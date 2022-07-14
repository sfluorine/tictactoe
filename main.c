#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static char board[3][3] = {
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
};

void draw_row(int col) {
  printf("|");

  for (int i = 0; i < 3; i++) {
    if (board[col][i] == 0)
      printf(" 0 |");
    else
      printf(" %c |", board[col][i]);
  }
  printf("\n");
}

void draw_board() {
  printf("==============\n");
  for (int i = 0; i < 3; i++)
    draw_row(i);
  printf("==============\n");
}

typedef struct {
  int x;
  int y;
} index_pair_t;

index_pair_t translate_index(int index) {
  index_pair_t pair;
  if (index <= 3) {
    pair.x = 0;
    pair.y = index - 1;
  } else if (index <= 6) {
    pair.x = 1;
    pair.y = index - 4;
  } else {
    pair.x = 2;
    pair.y = index - 7;
  }
  return pair;
}

void insert_board(int player, index_pair_t ip) {
  if (player == 0) {
    board[ip.x][ip.y] = 'O';
  } else {
    board[ip.x][ip.y] = 'X';
  }
}

bool try_insert_board(int player, int index) {
  index_pair_t ip = translate_index(index);

  if (board[ip.x][ip.y] != 0)
      return false;

  insert_board(player, ip);
  return true;
}

bool all_occupied() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == 0)
        return false;
    }
  }
  return true;
}

int check_winner() {
  // check horizontal O
  if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
    return 0;
  if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
    return 0;
  if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
    return 0;

  // check vertical O
  if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
    return 0;
  if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
    return 0;
  if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
    return 0;

  //check diagonal O
  if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
    return 0;
  if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
    return 0;

  // check horizontal X
  if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
    return 1;
  if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
    return 1;
  if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
    return 1;

  // check vertical X
  if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
    return 1;
  if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
    return 1;
  if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
    return 1;

  //check diagonal X
  if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
    return 1;
  if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
    return 1;

  return 3;
}

void print_winner(int winner) {
  if (winner == 0) {
    printf("player 1 win!\n");
  } else if (winner == 1) {
    printf("player 2 win!\n");
  } else {
    printf("draw!\n");
  }
}

int main(void) {
  int player = 0;

  do {
    draw_board();
    int input;
    scanf("%d", &input);
    
    if (input < 1 || input > 9) {
      fprintf(stderr, "please input valid index!\n");
      continue;
    }

    if (!try_insert_board(player, input)) {
      fprintf(stderr, "%d is already occupied!\n", input);
      continue;
    }

    int winner = check_winner();
    if (winner != 3) {
      draw_board();
      print_winner(winner);
      return 0;
    }

    player = !player;
    system("clear");
  } while (!all_occupied());
  
  draw_board();
  print_winner(check_winner());
}
