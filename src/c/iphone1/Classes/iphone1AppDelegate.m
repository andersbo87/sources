//
//  iphone1AppDelegate.m
//  iphone1
//
//  Created by Anders Bolt-Evensen on 1/8/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "iphone1AppDelegate.h"
#import "MainViewController.h"

@implementation iphone1AppDelegate


@synthesize window;
@synthesize mainViewController;


- (void)applicationDidFinishLaunching:(UIApplication *)application {
    
	MainViewController *aController = [[MainViewController alloc] initWithNibName:@"MainView" bundle:nil];
	self.mainViewController = aController;
	[aController release];
	
    mainViewController.view.frame = [UIScreen mainScreen].applicationFrame;
	[window addSubview:[mainViewController view]];
    [window makeKeyAndVisible];
}


- (void)dealloc {
    [mainViewController release];
    [window release];
    [super dealloc];
}

@end
