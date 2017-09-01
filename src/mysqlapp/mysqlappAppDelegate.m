//
//  mysqlappAppDelegate.m
//  mysqlapp
//
//  Created by Anders Bolt-Evensen on 9/12/10.
//  Copyright 2010 Høgskolen i Østfold. All rights reserved.
//

#import "mysqlappAppDelegate.h"
#import <MCPKit/MCPKit.h>

@implementation mysqlappAppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
	/*MCPConnection *conn = [[MCPConnection alloc]
						   
						   initToHost:@"localhost"
						   
						   withLogin:@"user"
						   
						   usingPort:3306];
	
	[conn setPassword: @"password"];
	
	// if connection successful, NSLog will show
	
	// "Connect: 1".
	
	NSLog(@"	 Connect: %d", [conn connect]);*/
}

@end
