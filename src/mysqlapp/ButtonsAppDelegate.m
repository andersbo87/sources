//
//  ButtonsAppDelegate.m
//  mysqlapp
//
//  Created by Anders Bolt-Evensen on 9/12/10.
//  Copyright 2010 Høgskolen i Østfold. All rights reserved.
//

#import "ButtonsAppDelegate.h"
#import "mysqlappAppDelegate.h"
#import <MCPKit/MCPKit.h>

@implementation ButtonsAppDelegate
@synthesize label;
@synthesize hostLabel;
@synthesize userLabel;
@synthesize passwordLabel;

@synthesize host;
@synthesize username;
@synthesize password;

-(IBAction)buttonPressed:(id)sender{
	//NSString *title = [sender title];
	NSString *t2 = [sender title];
	int i = 0;
		
	NSString *h = [host stringValue];
	//NSString *h = [NSString stringWithFormat:@"%@",host getStringValue:h];
	NSString *u = [username stringValue];
	NSString *p = [password stringValue];
	MCPConnection *conn = [[MCPConnection alloc]
						   
						   //initToHost:@"localhost"
						   initToHost:h
						   //withLogin:@"root"
						   withLogin:u
						   usingPort:3306];
	
	//[conn setPassword: @"klaand"];
	[conn setPassword:p];
	/*NSString *hostLabelText = [NSString stringWithFormat:@"%@",h];
	[hostLabel setStringValue:hostLabelText];*/
	// if connection successful, NSLog will show
	
	// "Connect: 1".
	i = [conn connect];
	//if the connect is successful, conn has the value of 1.
	if([conn connect] == 1)
	{
		NSString *labelText = [NSString stringWithFormat:@"You are connected to MySQL. "];
		[label setStringValue:labelText];
	}
	else 
	{
		NSString *labelText = [NSString stringWithFormat:@"Could not connect to MySQL. Click the button to try again. %d", [conn connect]];
		[label setStringValue:labelText];
	}
	//prints the connection value to /dev/console (or the system console)
	NSLog(@"	 Connect: %d", [conn connect]);
}


@end
