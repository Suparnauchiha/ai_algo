#include <stdio.h>
#include <stdbool.h>
#define MAX_STEPS 20

typedef struct {
    int jug1, jug2;
    const char* action;
    int poured;  // Amount of water moved/added/removed
} State;

bool isDuplicate(State history[], int count, int j1, int j2) {
    for (int i = 0; i < count; i++) {
        if (history[i].jug1 == j1 && history[i].jug2 == j2) return true;
    }
    return false;
}

void solveJugs(int cap1, int cap2, int target) {
    State history[MAX_STEPS];
    int steps = 0;
    
    printf("Solving for: Jug1(%dL), Jug2(%dL), Target=%dL\n", cap1, cap2, target);
    printf("Step: Action -> [Jug1,Jug2] = Total | Details\n");
    
    history[steps].jug1 = 0;
    history[steps].jug2 = 0;
    history[steps].action = "Initial state";
    history[steps].poured = 0;
    steps++;
    
    for (int i = 0; i < steps && steps < MAX_STEPS; i++) {
        int j1 = history[i].jug1;
        int j2 = history[i].jug2;
        
        if (j1 + j2 == target) {
            for (int j = 0; j < steps; j++) {
                printf("%d: %s -> [%d,%d] = %dL", j + 1, 
                       history[j].action, history[j].jug1, history[j].jug2,
                       history[j].jug1 + history[j].jug2);
                if (history[j].poured > 0) {
                    printf(" | %dL moved", history[j].poured);
                }
                printf("\n");
            }
            return;
        }
        
        if (j1 < cap1 && !isDuplicate(history, steps, cap1, j2)) {
            history[steps].jug1 = cap1;
            history[steps].jug2 = j2;
            history[steps].action = "Fill Jug1";
            history[steps].poured = cap1 - j1;
            steps++;
        }
        
        if (j2 < cap2 && !isDuplicate(history, steps, j1, cap2)) {
            history[steps].jug1 = j1;
            history[steps].jug2 = cap2;
            history[steps].action = "Fill Jug2";
            history[steps].poured = cap2 - j2;
            steps++;
        }
        
        if (j1 > 0 && !isDuplicate(history, steps, 0, j2)) {
            history[steps].jug1 = 0;
            history[steps].jug2 = j2;
            history[steps].action = "Empty Jug1";
            history[steps].poured = j1;
            steps++;
        }
        
        if (j2 > 0 && !isDuplicate(history, steps, j1, 0)) {
            history[steps].jug1 = j1;
            history[steps].jug2 = 0;
            history[steps].action = "Empty Jug2";
            history[steps].poured = j2;
            steps++;
        }
        
        if (j1 > 0 && j2 < cap2) {
            int pour = (j1 + j2 <= cap2) ? j1 : cap2 - j2;
            if (!isDuplicate(history, steps, j1 - pour, j2 + pour)) {
                history[steps].jug1 = j1 - pour;
                history[steps].jug2 = j2 + pour;
                history[steps].action = "Pour Jug1->Jug2";
                history[steps].poured = pour;
                steps++;
            }
        }
        
        if (j2 > 0 && j1 < cap1) {
            int pour = (j1 + j2 <= cap1) ? j2 : cap1 - j1;
            if (!isDuplicate(history, steps, j1 + pour, j2 - pour)) {
                history[steps].jug1 = j1 + pour;
                history[steps].jug2 = j2 - pour;
                history[steps].action = "Pour Jug2->Jug1";
                history[steps].poured = pour;
                steps++;
            }
        }
    }
    
    printf("No solution found within %d steps\n", MAX_STEPS);
}

int main() {
    solveJugs(4, 3, 2);
    return 0;
}
