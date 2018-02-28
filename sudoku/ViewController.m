//
//  ViewController.m
//  sudoku
//
//  Created by Jose Rojas on 12/21/14.
//  Copyright (c) 2014 Jose Rojas. All rights reserved.
//

/*
 * The ViewController generates all of the UI for the application.  The Sudoku game board is programatically generated so that it
 * can be easily resized. Its dimensions are dynamically calculated so that the game board is one half the height of the screen
 * so that it is not obscured by the soft keyboard.
 *
 * This class relies on the SudokuGenerator, Puzzle, Solution, and Position classes to generate a new Sudoku puzzle,
 * display its contents, and validate the results.
 *
 * The #define are here for educational purposes. I've used them to demonstrate the different aspects of programmatic UI
 * development.
 *
 * The game board consists of 81 cells that each contain a UILabel or UITextView. When a new puzzle is generated, if thex
 * value of the puzzle cell is 0, a UITextView is used, otherwise a UILabel is used. This allows cells that immutable
 * in the puzzle to not be edited, while those that are mutable can be selected and have their values changed by the
 * user.
 *
 * A UISegmentedControl is dynamically placed underneath the grid to act as a simple menu system. The user can create
 * a new puzzle, change the game difficulty, show the solution, or validate their current game state against the
 * solution.
 *
 */


#import "ViewController.h"
#import "Puzzle.h"
#import "Solution.h"
#import "Position.h"
#import "SudokuGenerator.h"
#import "CERewardedVideoAD.h"
#import "CESplash2AD.h"
#import "AppDelegate.h"
#import "AudioPlayHandler.h"

#import <QuartzCore/QuartzCore.h>

#define SHOW_GRIDVIEW
#define SHOW_PUZZLE
#define SHOW_NUMBERS
#define TEXT_COLOR
#define ENABLE_TEXT_FILTERING
#define SHOW_TOOLBAR
#define ENABLE_ANIMATIONS

static int SHOW_SPLASH_ADS = 0;
static int TOTAL_CHECK_TIMES = 3;
static int CHECK_STATUS_NORMAL = 0;
static int CHECK_STATUS_SHOW_SPLASH_ADS = 1;
static int CHECK_STATUS_COMPLETE = 2;
int checkTime = 3;
int checkingStatus = 0;
Boolean backFromNewPage = false;
UITextField *postTextField;

@interface ViewController () <CERewardedVideoADDelegate>
{
    CERewardedVideoAD *ceRewardedVideoAD;
}
@end

@interface ViewController() <CESplash2ADDelegate>{
    CESplash2AD *ceSplash2AD;
}
@end

@interface ViewController()
{
    UILabel *progress;
    NSTimer *timer;
    int currMinute;
    int currSeconds;
    
    UIImageView *alertBackGround;
    UIImage *backGroundPic;
    UIView *alertView;
    UILabel *textLabel;
    UILabel *remainCheck;
    UIButton *askCheck;
    UIButton *closeWindow;
}
@end


@implementation ViewController {
    UISegmentedControl *_toolbar;
    UIView* _gridview;
    bool _bShowSolution;
    PuzzleDifficulty _difficulty;
    SudokuGenerator * _generator;
}


/* The view controller loads all initial UI here */

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    _difficulty = PuzzleDifficultyEasy;
    _generator = [[SudokuGenerator alloc] init];

    // Do any additional setup after loading the view, typically from a nib.
    
    // grid view
    
#ifdef SHOW_GRIDVIEW
    [self createGridView];
#endif
    
#ifdef SHOW_PUZZLE
    [self newPuzzle];
#endif

/*#ifdef SHOW_TOOLBAR
    [self createToolbar];
#endif*/
    
#ifdef CHECK_TIME
    self.checkTimeView.text = [NSString stringWithFormat:@"%d",checkTime];
#endif
     
}

- (IBAction)clickResultAction:(id)sender {
    [self setAlertWindow];
}

- (void) setAlertWindow{
    
    UIImage *watchAD = [UIImage imageNamed:@"watchad"];
    UIImage *pressWatch = [UIImage imageNamed:@"press_watchad"];
    
    [[[UIApplication sharedApplication] keyWindow] endEditing:YES];

    alertBackGround = [[UIImageView alloc] initWithFrame: CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    backGroundPic = [UIImage imageNamed:@"alert_bg"];
    alertBackGround.image = backGroundPic;
    
    _clickButton.userInteractionEnabled = NO;
    _solveButton.userInteractionEnabled = NO;
    
    alertView = [[UIView alloc]initWithFrame:CGRectMake(48, 123, 295, 372)];
    [alertView setBackgroundColor:[UIColor colorWithRed:0.98 green:0.58 blue:0.45 alpha:1]];
    alertView.layer.cornerRadius = 24;
    alertView.layer.position = CGPointMake(self.view.frame.size.width/2, self.view.frame.size.height/2);
    
    textLabel = [[UILabel alloc]initWithFrame:CGRectMake(84, 202, 208, 47)];
    textLabel.layer.masksToBounds = TRUE;
    textLabel.text = [NSString stringWithFormat:@"Need help?"];
    textLabel.textColor = [UIColor whiteColor];
    textLabel.font = [UIFont boldSystemFontOfSize:40];
    textLabel.textAlignment = NSTextAlignmentCenter;
    textLabel.layer.position = CGPointMake(alertView.frame.size.width/2, 95);
    
    remainCheck = [[UILabel alloc]initWithFrame:CGRectMake(121, 255, 133, 25)];
    remainCheck.layer.masksToBounds = TRUE;
    remainCheck.text = [NSString stringWithFormat:@"Hints left:%d",checkTime];
    remainCheck.textColor = [UIColor whiteColor];
    remainCheck.font = [UIFont systemFontOfSize:20];
    remainCheck.textAlignment = NSTextAlignmentCenter;
    remainCheck.layer.position = CGPointMake(alertView.frame.size.width/2, 135);
    
    askCheck = [UIButton buttonWithType:UIButtonTypeSystem];
    askCheck = [[UIButton alloc]initWithFrame:CGRectMake(95.5, 311, 184, 54)];
    askCheck.layer.masksToBounds = TRUE;
    askCheck.layer.cornerRadius = 12;
    if( checkTime > 0 )
    {
        askCheck.layer.shadowOpacity = 0.5;
        askCheck.layer.shadowColor = [UIColor blackColor].CGColor;
        askCheck.layer.shadowOffset = CGSizeMake(0.0, 2.0);
        [askCheck setBackgroundColor: [UIColor whiteColor]];
    }
    
    
    [askCheck setTitleColor: [UIColor colorWithRed:0.98 green:0.58 blue:0.45 alpha:1] forState:UIControlStateNormal];
    [askCheck setTitleColor:[UIColor whiteColor] forState:UIControlStateHighlighted];
    askCheck.titleLabel.font = [UIFont boldSystemFontOfSize: 24];
    if(checkTime > 0 )
        [askCheck setTitle: @"Hint" forState:UIControlStateNormal];
    else if (checkTime == 0)
    {
        [askCheck setImage:watchAD forState:UIControlStateNormal];
        [askCheck setImage:pressWatch forState:UIControlStateHighlighted];
    }
    

    askCheck.layer.position = CGPointMake(alertView.frame.size.width/2, 264);
    [askCheck addTarget:self action:@selector(pressCheck:) forControlEvents:UIControlEventTouchDown];
    [askCheck addTarget:self action:@selector(confirmCheck:) forControlEvents:UIControlEventTouchUpInside];
    
    closeWindow = [[UIButton alloc]initWithFrame:CGRectMake(95.5, 384, 184, 54)];
    closeWindow.layer.masksToBounds = TRUE;
    closeWindow.layer.cornerRadius = 12;
    [closeWindow.layer setBorderColor: [UIColor whiteColor].CGColor];
    [closeWindow.layer setBorderWidth:2.0];
    [closeWindow setBackgroundColor: [UIColor colorWithRed:0.98 green:0.58 blue:0.45 alpha:1]];
    [closeWindow setTitleColor: [UIColor whiteColor] forState:UIControlStateNormal];
    [closeWindow setTitleColor:[UIColor colorWithRed:0.98 green:0.58 blue:0.45 alpha:1] forState:UIControlStateHighlighted];

    closeWindow.titleLabel.font = [UIFont boldSystemFontOfSize: 24];
    [closeWindow setTitle:@"Close" forState:UIControlStateNormal];
    closeWindow.layer.position = CGPointMake(alertView.frame.size.width/2, 324);
    [closeWindow addTarget:self action:@selector(pressClose:) forControlEvents:UIControlEventTouchDown];
    [closeWindow addTarget:self action:@selector(closeAlert:) forControlEvents:UIControlEventTouchUpInside];
    
    //[alertBackGround addSubview:alertView];
    [alertView addSubview:textLabel];
    [alertView addSubview:remainCheck];
    [alertView addSubview:askCheck];
    [alertView addSubview:closeWindow];
    [self.view addSubview:alertBackGround];
    [self.view addSubview:alertView];
    
    CAKeyframeAnimation *popAnimation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
    popAnimation.duration = 0.9;
    popAnimation.values = @[[NSValue valueWithCATransform3D:CATransform3DMakeScale(0.01f, 0.01f, 1.0f)],
                            [NSValue valueWithCATransform3D:CATransform3DMakeScale(1.1f, 1.1f, 1.0f)],
                            [NSValue valueWithCATransform3D:CATransform3DMakeScale(0.93f, 0.93f, 0.9f)],
                            [NSValue valueWithCATransform3D:CATransform3DIdentity]];
    popAnimation.keyTimes = @[@0.15f, @0.6f, @0.8f, @1.0f];
    popAnimation.timingFunctions = @[[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut],
                                     [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut],
                                     [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut]];
    [alertView.layer addAnimation:popAnimation forKey:nil];
}

- (void)closePopWindow
{
    [[[UIApplication sharedApplication] keyWindow] endEditing:NO];
    _clickButton.userInteractionEnabled = YES;
    _solveButton.userInteractionEnabled = YES;
    [alertView removeFromSuperview];
    [alertBackGround removeFromSuperview];
}

- (void)pressCheck:(UIButton *)sender
{
    sender.backgroundColor = [UIColor colorWithRed:1.0 green:0.70 blue:0.60 alpha:1];
    sender.layer.shadowOpacity = 0.4;
    sender.layer.shadowColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.5].CGColor;
    sender.layer.shadowOffset = CGSizeMake( 0, 0);
}

- (void)pressClose:(UIButton *)sender
{
    sender.backgroundColor = [UIColor whiteColor];
    sender.layer.shadowOpacity = 0.4;
    sender.layer.shadowColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.5].CGColor;
    sender.layer.shadowOffset = CGSizeMake( 0, 0);
}

- (IBAction)confirmCheck:(id)sender
{
    if(checkTime == SHOW_SPLASH_ADS){
        [self rewardedVideoADDidRequest];
        checkTime = TOTAL_CHECK_TIMES+1;
        checkingStatus = CHECK_STATUS_SHOW_SPLASH_ADS;
    } else {
        checkingStatus = CHECK_STATUS_NORMAL;
    }
    [self validateGrid];
    [self closePopWindow];
}

-(IBAction)closeAlert:(id)sender
{
    CAKeyframeAnimation *hideAnimation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
    hideAnimation.duration = 0.3;
    hideAnimation.values = @[[NSValue valueWithCATransform3D:CATransform3DMakeScale(1.1f, 1.1f, 1.0f)],
                             [NSValue valueWithCATransform3D:CATransform3DMakeScale(1.0f, 1.0f, 1.0f)],
                             [NSValue valueWithCATransform3D:CATransform3DMakeScale(0.00f, 0.00f, 0.00f)]];
    hideAnimation.keyTimes = @[@0.2f, @0.5f, @0.75f];
    hideAnimation.timingFunctions = @[[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut],
                                      [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut],
                                      [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut]];
    hideAnimation.delegate = self;
    [alertView.layer addAnimation:hideAnimation forKey:nil];
}

-(void) animationDidStop:(CAAnimation *)anim finished:(BOOL)flag
{
    [self closePopWindow];
}

- (IBAction)showAnswerAction:(id)sender {
    //[self rewardedVideoADDidRequest];
    for (UIView* view in _gridview.subviews)
        [view removeFromSuperview];
    [self layoutGrid:self.puzzle.solution];
    [self countdwonStart];
    //[alertBackGround removeFromSuperview];
}


- (void) createGridView {
    UIView* gridview = _gridview = [UIView new];
    CGRect rect = self.view.frame;
    rect.size.width -= 27;
    rect.size.width = rect.size.height / 2 < rect.size.width ? rect.size.height / 2 : rect.size.width;
    rect.size.width -= (int) rect.size.width % 9;
    rect.size.width += 2;
    rect.size.height = rect.size.width;
    rect.origin.x += (self.view.frame.size.width - rect.size.width) / 2;
    rect.origin.y += 100;

    gridview.frame = rect;
    gridview.backgroundColor = [UIColor whiteColor];
    
    [self.view addSubview:gridview];

}

- (void)appendLog:(NSString *)log {
    NSString* format = @"HH:mm:ss.SSS";
    
    // Set up an NSDateFormatter for UTC time zone
    NSDateFormatter* dateFtr = [[NSDateFormatter alloc] init];
    [dateFtr setDateFormat:format];
    [dateFtr setTimeZone:[NSTimeZone localTimeZone]];
    
    NSLog(@"%@", log);
    self.logTextView.text = [NSString stringWithFormat:@"%@  %@\n%@", [dateFtr stringFromDate:[NSDate date]], log, self.logTextView.text];
}

- (void) newPuzzle {
    [self newPuzzleWithSolution:nil];
}

- (void) newPuzzleWithSolution: (Solution *) solution {
    Puzzle* puzzle = nil;

    if (solution == nil)
        puzzle = [_generator generate: _difficulty];
    else
        puzzle = [_generator generatePuzzleWithSolution:solution difficulty:_difficulty];

    [puzzle.solution printGrid];
    [puzzle.grid printGrid];

    self.puzzle = puzzle;

    for (UIView* view in _gridview.subviews)
        [view removeFromSuperview];

    [self layoutGrid:_bShowSolution ? self.puzzle.solution : self.puzzle.grid];

    // Do animations
#ifdef ENABLE_ANIMATIONS
    _gridview.alpha = 0.0;

    [UIView animateWithDuration:0.5 animations:^() {
        _gridview.alpha = 1.0f;
    }];
#endif
}


- (void) validateGrid {
    checkTime --;
    Boolean isComplete = true;
    
    for (UIView* view in _gridview.subviews) {
        if ([view isKindOfClass:[UITextField class]]) {
            UITextField * textField = (UITextField *) view;
            int tag = (int) view.tag;
            UIColor * color = [_puzzle.grid positionAtIndex:tag].value.integerValue ==
                              [_puzzle.solution positionAtIndex:tag].value.integerValue ?
                [UIColor blackColor] :
                [UIColor colorWithRed:0.97 green:0.58 blue:0.54 alpha:1.0];
            if(!([_puzzle.grid positionAtIndex:tag].value.integerValue == [_puzzle.solution positionAtIndex:tag].value.integerValue) ||
               ([_puzzle.grid positionAtIndex:tag].value.integerValue == 0)) {
                   isComplete = false;
               }
            textField.textColor = color;
        }
    }
    
    [self.checkTimeView setValue:[NSString stringWithFormat:@"%d",checkTime] forKey:@"text"];
}

- (void) layoutGrid: (Solution*) solutionToShow {

    UIView* gridview = _gridview;
    CGRect rect = _gridview.frame;

    //determine the width/height of the grid items
    CGFloat sizeOfSquares = (rect.size.width - 2) / 9;
    
    //rows
    for (int i = 0; i < 9; i++) {
        //cols
        for (int j = 0; j < 9; j++) {

            UILabel * label = nil;

#ifndef SHOW_NUMBERS
            label = [self generateLabel: [Position new]];
#else
            //generate a grid item based on the data in the grid
            Position * pos = [solutionToShow getAtX:j Y:i];
            
            if (pos.value.integerValue != 0 && !pos.temporary) {
                label = [self generateLabel: pos];
            } else {
                label = [self generateTextField: pos];
            }
#endif
            
            //mark the grid item with a number for tracking purposes
            label.tag = i * 9 + j;
            
            //center align all the text in the grid item
            label.textAlignment = NSTextAlignmentCenter;

            //Set up the position and boundary for each grid item
            rect = CGRectMake(j * sizeOfSquares, i * sizeOfSquares,
                              sizeOfSquares + 2, sizeOfSquares + 2);
            label.frame = rect;
            
            //set up the colors for the grid item
            label.layer.borderColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0].CGColor;
            label.layer.borderWidth = 3;

            //add the grid item to the parent gridview
            [gridview addSubview:label];
        }
    }
    gridview.backgroundColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0];
    //draw 4 views to represent grid lines
    [self drawGridLines: rect sizeOfSquares:(int) sizeOfSquares];
}

- (UITextField*) generateLabel: (Position*) pos {
    UITextField* label = [UITextField new];
    label.text = pos.value.stringValue;
    label.layer.backgroundColor = [UIColor whiteColor].CGColor;
    label.layer.cornerRadius = 4;
    label.textColor = [UIColor darkGrayColor];
    label.userInteractionEnabled = NO;
    
    return label;
}

- (UITextField*) generateTextField: (Position*) pos {
    pos.temporary = YES;
    UITextField* label = [UITextField new];
    if (pos.value.integerValue != 0)
        label.text = pos.value.stringValue;
    label.layer.backgroundColor = [UIColor whiteColor].CGColor;
    label.layer.cornerRadius = 4;
#ifndef TEXT_COLOR
    label.textColor = [UIColor darkGrayColor];
#else
    //Change font size for editable text
    label.textColor = [UIColor blackColor];
    UIFontDescriptor * fontD = [label.font.fontDescriptor fontDescriptorWithSymbolicTraits:UIFontDescriptorTraitBold];
    label.font = [UIFont fontWithDescriptor: fontD size:label.font.pointSize + 2];
#endif
    
    label.keyboardType = UIKeyboardTypeNumberPad;
    label.clearsOnBeginEditing = true;
    label.delegate = self;
    [[label valueForKey:@"textInputTraits"] setValue:[UIColor clearColor] forKey:@"insertionPointColor"];
    [label addTarget:self
              action:@selector(textFieldDidChange:)
    forControlEvents:UIControlEventEditingChanged];
    
    [label addTarget:self action:@selector(handleButtonClicked:) forControlEvents:UIControlEventTouchUpInside];
    
    return label;
}

- (void) textFieldDidBeginEditing:(UITextField*)textField {
    NSLog(@"--------textFieldDidBeginEditing:%@",textField.text);
    if(postTextField != NULL){
        postTextField.layer.borderColor = [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1.0].CGColor;
    }
    postTextField = textField;
    CGFloat sizeOfSquares = (_gridview.frame.size.width - 2) / 9;
    //draw 4 views to represent grid lines
    [self drawGridLines: _gridview.frame sizeOfSquares:(int) sizeOfSquares];
    textField.layer.borderColor = [UIColor colorWithRed:0.97 green:0.58 blue:0.54 alpha:1.0].CGColor;
    textField.layer.borderWidth = 3;
    UIView* gridview = _gridview;
    //add the grid item to the parent gridvie
    [gridview addSubview:textField];

    NSLog(@"--------textFieldDidBeginEditing:%i",textField.tag);
}

- (void) drawGridLines: (CGRect) rect sizeOfSquares: (int) sizeOfSquares {
    UIView* line = [UILabel new];
    
    rect = CGRectMake(0, sizeOfSquares * 3, sizeOfSquares * 9 + 2, 2);
    line.frame = rect;
    line.layer.backgroundColor = [UIColor colorWithRed:0.6 green:0.6 blue:0.6 alpha:1.0].CGColor;
    
    [_gridview addSubview:line];
    
    line = [UILabel new];
    rect = CGRectMake(0, sizeOfSquares * 6, sizeOfSquares * 9 + 2, 2);
    line.frame = rect;
    line.layer.backgroundColor = [UIColor colorWithRed:0.6 green:0.6 blue:0.6 alpha:1.0].CGColor;;
    
    [_gridview addSubview:line];
    
    line = [UILabel new];
    rect = CGRectMake(sizeOfSquares * 3, 0, 2, sizeOfSquares * 9 + 2);
    line.frame = rect;
    line.layer.backgroundColor = [UIColor colorWithRed:0.6 green:0.6 blue:0.6 alpha:1.0].CGColor;
    
    [_gridview addSubview:line];
    
    line = [UILabel new];
    rect = CGRectMake(sizeOfSquares * 6, 0, 2, sizeOfSquares * 9 + 2);
    line.frame = rect;
    line.layer.backgroundColor = [UIColor colorWithRed:0.6 green:0.6 blue:0.6 alpha:1.0].CGColor;
    
    [_gridview addSubview:line];

}

- (void) textFieldDidChange: (UITextField*) field {
    //update the user grid
    NSInteger index = field.tag;

    [_puzzle.grid positionAtIndex: index].value = @(field.text.integerValue);
    
#ifndef TEXT_COLOR
    field.textColor = [UIColor darkGrayColor];
#else
    field.textColor = [UIColor blackColor];
#endif
}

-(void)countdwonStart
{
    currMinute = 0;
    currSeconds = 01;
    timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(timerFired) userInfo:nil repeats:YES];

}
-(void)timerFired
{
    if((currMinute>0 || currSeconds>=0) && currMinute>=0)
    {
        if(currSeconds==0)
        {
            currMinute-=1;
            currSeconds=59;
        }
        else if(currSeconds>0)
        {
            currSeconds-=1;
        }
    }
    else
    {
        backFromNewPage = true;
        [timer invalidate];
        [self performSegueWithIdentifier:@"goToNewPage" sender:self];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


/*!
 *  @brief callback while fail to load a rewardedVideo ad from CrystalExpressSDK
 *
 *  @param rewardedVideoAD CERewardedVideoAD instance that own this rewardedVideo ad component
 *  @param error error indicates the fail reason
 */
- (void)rewardedVideoADDidFail:(CERewardedVideoAD *)rewardedVideoAD withError:(NSError *)error
{
    [self appendLog:[NSString stringWithFormat:@"rewardedVideoADDidFail, error : %@", error.description]];;
}

- (void)rewardedVideoADDidVideoStart:(CERewardedVideoAD *)rewardedVideoAD
{
    [AudioPlayHandler pauseBackgroundMusic];
    [self appendLog:@"rewardedVideoADDidVideoStart"];
}

- (void) rewardedVideoADWillDismiss:(nonnull CERewardedVideoAD *)rewardedVideoAD
{
    [AudioPlayHandler resumeBackgroundMusic];
    [self appendLog:@"rewardedVideoADWillDismiss"];
}

- (void) rewardedVideoADDidDismiss:(nonnull CERewardedVideoAD *)rewardedVideoAD
{
    backFromNewPage = true;
}

/*!
 *
 * @brief send rewarded viedo request to load ads, and it will display ads while loading successfully.
 *
 */
-(void) rewardedVideoADDidRequest
{
    ceRewardedVideoAD = [[CERewardedVideoAD alloc] initWithPlacement:@"HINT_REWARDED"];
    ceRewardedVideoAD.delegate = self;
    [ceRewardedVideoAD loadAd];
}

#pragma mark - CERewardedVideoADDelgate
- (void) rewardedVideoADDidLoaded:(CERewardedVideoAD*)rewardedVideoAD
{
    UIViewController *topController = [UIApplication sharedApplication].keyWindow.rootViewController;
    while (topController.presentedViewController) {
        topController = topController.presentedViewController;
    }

    [ceRewardedVideoAD showFromViewController:topController animated:YES];
}

/*!
 *
 * @brief send splash viedo request to load ads, and it will display ads while loading successfully.
 *
 */
-(void) splashADDidRequest
{
    ceSplash2AD = [[CESplash2AD alloc] initWithPlacement:@"END_INTERSTITUAL"];
    ceSplash2AD.delegate = self;
    [ceSplash2AD loadAd];
}

#pragma mark - CESplash2ADDelegate
- (void)splash2ADDidLoaded:(CESplash2AD*)splash2AD
{
    UIViewController *topController = [UIApplication sharedApplication].keyWindow.rootViewController;
    while (topController.presentedViewController) {
        topController = topController.presentedViewController;
    }
    
    [ceSplash2AD showFromViewController:topController animated:YES];
}

- (void) splash2ADDidVideoStart:(nonnull CESplash2AD *)splash2AD
{
    [AudioPlayHandler pauseBackgroundMusic];
    [self appendLog:@"splash2ADDidVideoStart"];
    [self.checkTimeView setValue:[NSString stringWithFormat:@"%d",checkTime] forKey:@"text"];
}

- (void) splash2ADWillDismiss:(nonnull CESplash2AD *)splash2AD
{
    [AudioPlayHandler resumeBackgroundMusic];
    [self appendLog:@"splash2ADWillDismiss"];
}


#ifdef ENABLE_TEXT_FILTERING
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if ([string isEqualToString:@"0"]) {
        textField.text = nil;
        return NO;
    }
    
    [textField deleteBackward];
    return YES;
}
#endif

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    if(backFromNewPage) {
        backFromNewPage = !backFromNewPage;
        [self newPuzzle];
    }
}

@end



void drawLine(int x1, int y1, int x2, int y2) {
    /* Get the current graphics context */
    CGContextRef currentContext = UIGraphicsGetCurrentContext();
    CGContextSetStrokeColorWithColor(currentContext, [UIColor blackColor].CGColor);

    /* Set the width for the line */
    CGContextSetLineWidth(currentContext, 2.0f);
    /* Start the line at this point */
    CGContextMoveToPoint(currentContext, x1, y1);
    /* And end it at this point */
    CGContextAddLineToPoint(currentContext, x2, y2);
    /* Use the context's current color to draw the line */
    CGContextStrokePath(currentContext);
}





