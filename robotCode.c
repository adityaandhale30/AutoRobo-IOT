// Define pins for IR sensors
const int left_sensor_pin = A0;
const int right_sensor_pin = A1;
const int forward_sensor_pin = A2;

// Define pins for motor driver
const int pwmA = 3;
const int IN1 = 4;
const int IN2 = 5;
const int pwmB = 6;
const int IN3 = 7;
const int IN4 = 8;

// Define motor speeds
int base_speed = 150; // Base speed for straight movement
int turn_speed = 100; // Speed for turning

// Define threshold values
int forward_threshold = 600; // Adjusted for maze width
int side_threshold = 600;    // Adjusted for maze width

void setup() {
  // Initialize motor pins
  pinMode(pwmA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Read sensor values
  int left_sensor = analogRead(left_sensor_pin);
  int right_sensor = analogRead(right_sensor_pin);
  int forward_sensor = analogRead(forward_sensor_pin);

  // Calculate error
  int left_error = side_threshold - left_sensor;
  int right_error = side_threshold - right_sensor;

  // Calculate motor speeds based on error
  int left_speed = base_speed + left_error * 0.5;
  int right_speed = base_speed + right_error * 0.5;

  // Follow the left side wall
  if (forward_sensor > forward_threshold) {
    // Move forward
    move_forward(left_speed, right_speed);
  } else if (left_sensor < side_threshold && right_sensor > side_threshold) {
    // Turn right
    turn_right(turn_speed);
  } else if (left_sensor > side_threshold && right_sensor < side_threshold) {
    // Turn left
    turn_left(turn_speed);
  } else {
    // Stop
    stop();
  }
}

void move_forward(int left_speed, int right_speed) {
  analogWrite(pwmA, left_speed);
  analogWrite(pwmB, right_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(50); // Delay for stabilization
}

void move_backward(int left_speed, int right_speed) {
  analogWrite(pwmA, left_speed);
  analogWrite(pwmB, right_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(50); // Delay for stabilization
}

void turn_left(int speed) {
  analogWrite(pwmA, speed);
  analogWrite(pwmB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500); // Delay for slower turning
}

void turn_right(int speed) {
  analogWrite(pwmA, speed);
  analogWrite(pwmB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500); // Delay for slower turning
}

void stop() {
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
  delay(50); // Delay for stabilization
}