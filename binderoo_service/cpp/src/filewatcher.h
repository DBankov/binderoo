/*
Binderoo
Copyright (c) 2016, Remedy Entertainment
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
* Neither the name of the copyright holder (Remedy Entertainment) nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL REMEDY ENTERTAINMENT BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
//----------------------------------------------------------------------------

#pragma once

#if !defined( _BINDEROO_SERVICE_FILEWATCHER_H_ )
#define _BINDEROO_SERVICE_FILEWATCHER_H_

#include "binderoo/defs.h"
#include "binderoo/allocator.h"
#include "binderoo/containers.h"
#include "binderoo/monitoredfolder.h"

namespace binderoo
{
	struct ChangedFiles
	{
		MonitoredFolder*												pThisFolder;
		Containers< AllocatorSpace::Service >::InternalString			strChangedFile;
	};
	//------------------------------------------------------------------------

	typedef std::vector< ChangedFiles, binderoo::Allocator< AllocatorSpace::Service, ChangedFiles > >					ChangedFilesVector;
	typedef std::vector< void*, binderoo::Allocator< AllocatorSpace::Service, void* > >									VoidPointerVector;
	//------------------------------------------------------------------------

	class FileWatcher
	{
	public:
		FileWatcher( Slice< MonitoredFolder >& folders );
		~FileWatcher();

		bool detectFileChanges();
		BIND_INLINE const ChangedFilesVector& getChangedFiles() const			{ return vecCurrentChangedFiles; }

		void getAllFiles( Containers< AllocatorSpace::Service >::StringVector& vecOutput );
		void getAllFiles( const MonitoredFolder& folder, Containers< AllocatorSpace::Service >::StringVector& vecOutput );
		void getAllFiles( const Containers< AllocatorSpace::Service >::InternalString& strFolder, const Containers< AllocatorSpace::Service >::InternalString& strExtensions, Containers< AllocatorSpace::Service >::StringVector& vecOutput );
		//--------------------------------------------------------------------

	private:
		Slice< MonitoredFolder >				monitoredFolders;
		VoidPointerVector						vecFileWatchersHandles;

		ChangedFilesVector						vecCurrentChangedFiles;
	};
	//------------------------------------------------------------------------
}
//----------------------------------------------------------------------------

#endif // !defined( _BINDEROO_SERVICE_FILEWATCHER_H_ )

//============================================================================
