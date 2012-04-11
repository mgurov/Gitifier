// -------------------------------------------------------
// GrowlController.h
//
// Copyright (c) 2010 Jakub Suder <jakub.suder@gmail.com>
// Licensed under Eclipse Public License v1.0
// -------------------------------------------------------

#import <Growl/GrowlApplicationBridge.h>

@class Commit;
@class Repository;
@class RepositoryListController;

extern NSString *OtherMessageGrowl;

@interface GrowlController : NSObject <GrowlApplicationBridgeDelegate> {
  RepositoryListController *repositoryListController;
}

@property RepositoryListController *repositoryListController;

// public
+ (GrowlController *) sharedController;
+ (BOOL) growlDetected;

- (void) showGrowlWithCommit: (Commit *) commit;
- (void) showGrowlWithNewBranch: (NSArray *) branch;
- (void) showGrowlWithCommitGroup: (NSArray *) commits includesAllCommits: (BOOL) includesAll;
- (void) showGrowlWithCommitGroupIncludingAllCommits: (NSArray *) commits;
- (void) showGrowlWithCommitGroupIncludingSomeCommits: (NSArray *) commits;

- (void) showGrowlWithError: (NSString *) message repository: (Repository *) repository;
- (void) showGrowlWithTitle: (NSString *) title message: (NSString *) message type: (NSString *) type;

// private
- (NSData *) growlIcon;

@end
