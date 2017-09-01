//
//  iphone1AppDelegate.h
//  iphone1
//
//  Created by Anders Bolt-Evensen on 1/8/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

@class MainViewController;

@interface iphone1AppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    MainViewController *mainViewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) MainViewController *mainViewController;

@end

