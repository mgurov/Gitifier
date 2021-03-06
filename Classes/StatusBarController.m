// -------------------------------------------------------
// StatusBarController.m
//
// Copyright (c) 2010 Jakub Suder <jakub.suder@gmail.com>
// Licensed under Eclipse Public License v1.0
// -------------------------------------------------------

#import "Commit.h"
#import "CommitWindowController.h"
#import "Defaults.h"
#import "StatusBarController.h"

static NSInteger RecentCommitsTitleLimit = 50;

@implementation StatusBarController

@synthesize statusBarMenu;

- (id) init {
  self = [super init];
  if (self) {
    recentCommits = [NSArray array];
  }
  return self;
}

- (void) createStatusBarItem {
  statusBarItem = [[NSStatusBar systemStatusBar] statusItemWithLength: NSSquareStatusItemLength];
  if (!statusBarItem) {
    NSRunAlertPanel(@"Error", @"Gitifier menu could not be created :(", @"That's a shame", nil, nil);
    [NSApp terminate: self];
  }

  statusBarItem.image = [NSImage imageNamed: @"icon_menu.png"];
  statusBarItem.alternateImage = [NSImage imageNamed: @"icon_menu_inverted.png"];
  statusBarItem.highlightMode = YES;
  statusBarItem.menu = statusBarMenu;
}

- (void) updateRecentCommitsList: (NSArray *) newCommits {
  NSInteger limit = [GitifierDefaults integerForKey: RecentCommitsListLengthKey];

  recentCommits = [newCommits arrayByAddingObjectsFromArray: recentCommits];
  recentCommits = [recentCommits subarrayWithRange: NSMakeRange(0, MIN(recentCommits.count, limit))];

  [self updateRecentCommitsSection];
}

- (void) updateRecentCommitsSection {
  NSMenu *menu = statusBarItem.menu;

  while ([[menu itemAtIndex: 0] representedObject]) {
    [menu removeItemAtIndex: 0];
  }

  if (![[menu itemAtIndex: 0] isSeparatorItem]) {
    [menu insertItem: [NSMenuItem separatorItem] atIndex: 0];
  }

  for (NSInteger i = 0; i < recentCommits.count; i++) {
    Commit *commit = [recentCommits objectAtIndex: i];

    NSString *title = commit.subject;
    if (title.length > RecentCommitsTitleLimit) {
      title = [[title substringToIndex: RecentCommitsTitleLimit - 1] stringByAppendingString: @"…"];
    }

    SEL action = @selector(commitEntryClickedInMenu:);
    NSMenuItem *item = [[NSMenuItem alloc] initWithTitle: title action: action keyEquivalent: @""];
    [item setRepresentedObject: commit];
    [item setTarget: self];
    [menu insertItem: item atIndex: i];
  }
}

- (void) commitEntryClickedInMenu: (id) sender {
  Commit *commit = [sender representedObject];

  if (commit) {
    [[[CommitWindowController alloc] initWithCommit: commit] show];
  }
}

@end
