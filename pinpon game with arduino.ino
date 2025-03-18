#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define PLAYER_SPEED 2
#define BALL_SPEED_X 4 
#define BALL_SPEED_Y 4 

#define PADDLE_WIDTH 3
#define PADDLE_HEIGHT 10
#define BALL_SIZE 2

#define PADDLE_GAP 5
#define PADDLE_OFFSET_X 2

#define LEFT_PADDLE_X PADDLE_OFFSET_X
#define RIGHT_PADDLE_X (SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_OFFSET_X)

#define BUTTON_LEFT_PIN 2
#define BUTTON_RIGHT_PIN 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int leftPaddleY = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
int rightPaddleY = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
int ballX = SCREEN_WIDTH / 2;
int ballY = SCREEN_HEIGHT / 2;
int ballXSpeed = -BALL_SPEED_X;
int ballYSpeed = BALL_SPEED_Y;

bool buttonLeftPressed = false;
bool buttonRightPressed = false;

int playerLeftScore = 0;
int playerRightScore = 0;

void setup() {
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // Clear the buffer
  display.clearDisplay();
  
  // Display custom startup text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, SCREEN_HEIGHT / 2 - 10);
  display.println("ArduinOman.store");
  display.display();
  delay(2000);  // Display the text for 2 seconds
  
  display.clearDisplay();
}

void loop() {
  readButtons();

  movePaddles();

  moveBall();

  display.clearDisplay();
  displayPaddles();
  displayBall();
  displayScores();
  display.display();

  delay(20);
}

void readButtons() {
  buttonLeftPressed = digitalRead(BUTTON_LEFT_PIN) == LOW;
  buttonRightPressed = digitalRead(BUTTON_RIGHT_PIN) == LOW;
}

void movePaddles() {
  // Move left paddle with button
  if (buttonLeftPressed && leftPaddleY > 0) {
    leftPaddleY -= PLAYER_SPEED;
  } else if (!buttonLeftPressed && leftPaddleY + PADDLE_HEIGHT < SCREEN_HEIGHT) {
    leftPaddleY += PLAYER_SPEED;
  }

  // Move right paddle with button
  if (buttonRightPressed && rightPaddleY > 0) {
    rightPaddleY -= PLAYER_SPEED;
  } else if (!buttonRightPressed && rightPaddleY + PADDLE_HEIGHT < SCREEN_HEIGHT) {
    rightPaddleY += PLAYER_SPEED;
  }
}

void moveBall() {
  ballX += ballXSpeed;
  ballY += ballYSpeed;

  // Ball collisions with top and bottom
  if (ballY <= 0 || ballY >= SCREEN_HEIGHT - BALL_SIZE) {
    ballYSpeed = -ballYSpeed;
  }

  // Ball collisions with paddles
  if ((ballX <= LEFT_PADDLE_X + PADDLE_WIDTH && ballX >= LEFT_PADDLE_X) ||
      (ballX + BALL_SIZE >= RIGHT_PADDLE_X && ballX + BALL_SIZE <= RIGHT_PADDLE_X + PADDLE_WIDTH)) {
    if ((ballY >= leftPaddleY && ballY <= leftPaddleY + PADDLE_HEIGHT) ||
        (ballY >= rightPaddleY && ballY <= rightPaddleY + PADDLE_HEIGHT)) {
      ballXSpeed = -ballXSpeed;
    }
  }

  // Ball out of bounds
  if (ballX <= 0) {
    // Reset ball position
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    // Reset ball speed and change direction
    ballXSpeed = -ballXSpeed;
    ballYSpeed = BALL_SPEED_Y;
    // Increment player right score
    playerRightScore++;
  } else if (ballX >= SCREEN_WIDTH - BALL_SIZE) {
    // Reset ball position
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    // Reset ball speed and change direction
    ballXSpeed = -ballXSpeed;
    ballYSpeed = BALL_SPEED_Y;
    // Increment player left score
    playerLeftScore++;
  }
}

void displayPaddles() {
  display.fillRect(LEFT_PADDLE_X, leftPaddleY, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
  display.fillRect(RIGHT_PADDLE_X, rightPaddleY, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
}

void displayBall() {
  display.fillRect(ballX, ballY, BALL_SIZE, BALL_SIZE, WHITE);
}

void displayScores() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.print("P1: ");
  display.print(playerLeftScore);
  display.setCursor(SCREEN_WIDTH - 70, 0);
  display.print("P2: ");
  display.print(playerRightScore);
}