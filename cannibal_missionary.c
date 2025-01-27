#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 3

typedef struct {
    int missionaries;
    int cannibals;
    int boat; // 1 means boat is on the starting side, 0 means on the opposite side
} State;

bool is_valid_state(State state) {
    // Check if state is valid
    if (state.missionaries < 0 || state.cannibals < 0 ||
        state.missionaries > MAX_PEOPLE || state.cannibals > MAX_PEOPLE) {
        return false;
    }
    // Check missionaries are not outnumbered by cannibals
    if ((state.missionaries > 0 && state.missionaries < state.cannibals) ||
        (MAX_PEOPLE - state.missionaries > 0 &&
         MAX_PEOPLE - state.missionaries < MAX_PEOPLE - state.cannibals)) {
        return false;
    }
    return true;
}

bool is_goal_state(State state) {
    // Goal is when all missionaries and cannibals are on the opposite side
    return state.missionaries == 0 && state.cannibals == 0 && state.boat == 0;
}

void print_state(State state) {
    printf("Missionaries: %d, Cannibals: %d, Boat: %s\n",
           state.missionaries, state.cannibals,
           state.boat ? "Starting Side" : "Opposite Side");
}

bool dfs(State current, State visited_states[], int depth) {
    // If the goal state is reached
    if (is_goal_state(current)) {
        print_state(current);
        return true;
    }

    // Mark the current state as visited
    visited_states[depth] = current;

    // Generate possible next states
    int moves[][2] = {
        {1, 0}, // 1 missionary
        {0, 1}, // 1 cannibal
        {2, 0}, // 2 missionaries
        {0, 2}, // 2 cannibals
        {1, 1}  // 1 missionary and 1 cannibal
    };

    for (int i = 0; i < 5; i++) {
        State next = current;
        int m = moves[i][0];
        int c = moves[i][1];

        if (current.boat == 1) {
            // Boat moving from starting side to opposite side
            next.missionaries -= m;
            next.cannibals -= c;
            next.boat = 0;
        } else {
            // Boat moving from opposite side to starting side
            next.missionaries += m;
            next.cannibals += c;
            next.boat = 1;
        }

        if (is_valid_state(next)) {
            // Check if next state has already been visited
            bool visited = false;
            for (int j = 0; j <= depth; j++) {
                if (visited_states[j].missionaries == next.missionaries &&
                    visited_states[j].cannibals == next.cannibals &&
                    visited_states[j].boat == next.boat) {
                    visited = true;
                    break;
                }
            }

            if (!visited) {
                if (dfs(next, visited_states, depth + 1)) {
                    print_state(current);
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    State initial = {MAX_PEOPLE, MAX_PEOPLE, 1};
    State visited_states[100]; // Large enough to hold all possible states

    printf("Solution to the Missionaries and Cannibals Problem:\n");
    if (!dfs(initial, visited_states, 0)) {
        printf("No solution found.\n");
    }

    return 0;
}
