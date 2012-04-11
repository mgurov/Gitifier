// -------------------------------------------------------
// Repository.h
//
// Copyright (c) 2010 Jakub Suder <jakub.suder@gmail.com>
// Licensed under Eclipse Public License v1.0
// -------------------------------------------------------

@class Repository;

typedef enum { ActiveRepository, UnavailableRepository } RepositoryStatus;

@protocol RepositoryDelegate
- (void) commitsReceived: (NSArray *) commits inRepository: (Repository *) repository;
- (void) newBranchDetected: (NSArray *) names inRepository: (Repository *) repository;
@end

// ------------------------------

@class Commit;
@class Git;

@interface Repository : NSObject {
  RepositoryStatus status;
  Git *git;
  NSString *url;
  NSString *name;
  NSString *commitUrlPattern;
  id delegate;
  BOOL isBeingUpdated;
}

@property (copy) NSString *url;
@property (copy) NSString *name;
@property id delegate;

// public
+ (Repository *) repositoryFromHash: (NSDictionary *) hash;
+ (Repository *) repositoryWithUrl: (NSString *) anUrl;
- (id) initWithUrl: (NSString *) anUrl;
- (void) clone;
- (void) fetchNewCommits;
- (void) cancelCommands;
- (void) deleteWorkingCopy;
- (void) resetStatus;
- (NSDictionary *) hashRepresentation;
- (NSString *) workingCopyDirectory;
- (BOOL) directoryExists: (NSString *) directory;
- (NSURL *) webUrlForCommit: (Commit *) commit;

// private
+ (NSDictionary *) repositoryUrlPatterns;
- (NSString *) findCommitUrlPattern;
- (BOOL) isProperUrl: (NSString *) url;
- (NSString *) nameFromUrl: (NSString *) anUrl;
- (NSString *) cachesDirectory;
- (void) notifyDelegateWithSelector: (SEL) selector;
- (BOOL) ensureDirectoryIsDeleted: (NSString *) directory;
- (BOOL) ensureDirectoryExists: (NSString *) directory;

@end
