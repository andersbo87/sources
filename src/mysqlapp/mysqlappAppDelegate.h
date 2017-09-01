//
//  mysqlappAppDelegate.h
//  mysqlapp
//
//  Created by Anders Bolt-Evensen on 9/12/10.
//  Copyright 2010 Høgskolen i Østfold. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface mysqlappAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
