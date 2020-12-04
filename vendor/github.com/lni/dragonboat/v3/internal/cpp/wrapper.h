// Copyright 2017-2019 Lei Ni (nilei81@gmail.com) and other Dragonboat authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INTERNAL_CPP_WRAPPER_H_
#define INTERNAL_CPP_WRAPPER_H_

#include <stdint.h>
#include "dragonboat/binding.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPPRegularStateMachine CPPRegularStateMachine;
typedef struct CPPConcurrentStateMachine CPPConcurrentStateMachine;
typedef struct CPPOnDiskStateMachine CPPOnDiskStateMachine;
typedef struct CollectedFiles CollectedFiles;
typedef struct LeaderInfo LeaderInfo;


void *LoadFactoryFromPlugin(char *soFilename, char *factoryName);

CPPRegularStateMachine *CreateDBRegularStateMachine(uint64_t clusterID,
  uint64_t nodeID, void *factory, uint64_t cStyle);
void DestroyDBRegularStateMachine(CPPRegularStateMachine *ds);
uint64_t UpdateDBRegularStateMachine(CPPRegularStateMachine *ds,
  uint64_t index, const unsigned char *cmd, size_t cmdLen);
LookupResult LookupDBRegularStateMachine(CPPRegularStateMachine *ds,
  const unsigned char *data, size_t size);
uint64_t GetHashDBRegularStateMachine(CPPRegularStateMachine *ds);
SnapshotResult SaveSnapshotDBRegularStateMachine(CPPRegularStateMachine *ds,
  uint64_t writerOID, uint64_t collectionOID, uint64_t doneChOID);
int RecoverFromSnapshotDBRegularStateMachine(CPPRegularStateMachine *ds,
  CollectedFiles *cf, uint64_t readerOID, uint64_t doneChOID);
void FreeLookupResultDBRegularStateMachine(CPPRegularStateMachine *ds,
  LookupResult r);

CPPConcurrentStateMachine *CreateDBConcurrentStateMachine(uint64_t clusterID,
  uint64_t nodeID, void *factory, uint64_t cStyle);
void DestroyDBConcurrentStateMachine(CPPConcurrentStateMachine *ds);
void BatchedUpdateDBConcurrentStateMachine(CPPConcurrentStateMachine *ds,
  Entry *entries, size_t size);
LookupResult LookupDBConcurrentStateMachine(CPPConcurrentStateMachine *ds,
  const unsigned char *data, size_t size);
uint64_t GetHashDBConcurrentStateMachine(CPPConcurrentStateMachine *ds);
PrepareSnapshotResult PrepareSnapshotDBConcurrentStateMachine(
  CPPConcurrentStateMachine *ds);
SnapshotResult SaveSnapshotDBConcurrentStateMachine(
  CPPConcurrentStateMachine *ds, const void *context,
  uint64_t writerOID, uint64_t collectionOID, uint64_t doneChOID);
int RecoverFromSnapshotDBConcurrentStateMachine(CPPConcurrentStateMachine *ds,
  CollectedFiles *cf, uint64_t readerOID, uint64_t doneChOID);
void FreeLookupResultDBConcurrentStateMachine(CPPConcurrentStateMachine *ds,
  LookupResult r);

CPPOnDiskStateMachine *CreateDBOnDiskStateMachine(uint64_t clusterID,
  uint64_t nodeID, void *factory, uint64_t cStyle);
void DestroyDBOnDiskStateMachine(CPPOnDiskStateMachine *ds);
OpenResult OpenDBOnDiskStateMachine(CPPOnDiskStateMachine *ds,
  uint64_t doneChOID);
void BatchedUpdateDBOnDiskStateMachine(CPPOnDiskStateMachine *ds,
  Entry *entries, size_t size);
LookupResult LookupDBOnDiskStateMachine(CPPOnDiskStateMachine *ds,
  const unsigned char *data, size_t size);
int SyncDBOnDiskStateMachine(CPPOnDiskStateMachine *ds);
uint64_t GetHashDBOnDiskStateMachine(CPPOnDiskStateMachine *ds);
PrepareSnapshotResult PrepareSnapshotDBOnDiskStateMachine(
  CPPOnDiskStateMachine *ds);
SnapshotResult SaveSnapshotDBOnDiskStateMachine(CPPOnDiskStateMachine *ds,
  const void *context, uint64_t writerOID, uint64_t doneChOID);
int RecoverFromSnapshotDBOnDiskStateMachine(CPPOnDiskStateMachine *ds,
  uint64_t readerOID, uint64_t doneChOID);
void FreeLookupResultDBOnDiskStateMachine(CPPOnDiskStateMachine *ds,
  LookupResult r);

CollectedFiles *GetCollectedFile();
void FreeCollectedFile(CollectedFiles *cf);
void AddToCollectedFile(CollectedFiles *cf, uint64_t fileID,
  const char *path, size_t pathLen, const unsigned char *metadata, size_t len);

void LeaderUpdated(void *listener, LeaderInfo info);

#ifdef __cplusplus
}
#endif

#endif  // INTERNAL_CPP_WRAPPER_H_
