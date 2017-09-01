//
//  ButtonsAppDelegate.h
//  mysqlapp
//
//  Created by Anders Bolt-Evensen on 9/12/10.
//  Copyright 2010 Høgskolen i Østfold. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface ButtonsAppDelegate : NSObject {
	//declaring label variables
	NSTextField *label;
	NSTextField *hostLabel;
	NSTextField *userLabel;
	NSTextField *passwordLabel;
	
	//declaring textbox variables:
	NSTextField *host;
	NSTextField *username;
	NSTextField *password;

}
@property IBOutlet NSTextField *label;
@property IBOutlet NSTextField *hostLabel;
@property IBOutlet NSTextField *userLabel;
@property IBOutlet NSTextField *passwordLabel;

@property IBOutlet NSTextField *host;
@property IBOutlet NSTextField *username;
@property IBOutlet NSTextField *password;

-(IBAction)buttonPressed:(id)sender;

@end
