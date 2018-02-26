//
//  ViewController.h
//  sudoku
//
//  Created by Jose Rojas on 12/21/14.
//  Copyright (c) 2014 Jose Rojas. All rights reserved.
//


#import <UIKit/UIKit.h>

@class Puzzle;

@interface ViewController : UIViewController<UIActionSheetDelegate, UITextFieldDelegate>

/* The current Sudoku Puzzle */
@property Puzzle * puzzle;
@property (weak, nonatomic) IBOutlet UITextView *logTextView;
@property (weak, nonatomic) IBOutlet UIButton *clickButton;
@property (weak, nonatomic) IBOutlet UIButton *solveButton;


@end
