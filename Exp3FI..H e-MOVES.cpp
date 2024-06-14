#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_STATES 100

// Structure to represent transitions in the NFA
struct transition {
    int state;
    struct transition *next;
};

// Structure to represent a state in the NFA
struct state {
    int state_num;
    struct transition *transitions;
};

// Function to initialize a state
void initialize_state(struct state *s, int num) {
    s->state_num = num;
    s->transitions = NULL;
}

// Function to add a transition to a state
void add_transition(struct state *s, int state) {
    struct transition *new_transition = (struct transition*)malloc(sizeof(struct transition));
    new_transition->state = state;
    new_transition->next = s->transitions;
    s->transitions = new_transition;
}

// Function to find e-closure of a state
void epsilon_closure(struct state nfa[], int state_num, bool visited[]) {
    if (visited[state_num])
        return;

    visited[state_num] = true;
    printf("%d ", state_num);

    struct transition *transition = nfa[state_num].transitions;

    while (transition != NULL) {
        epsilon_closure(nfa, transition->state, visited);
        transition = transition->next;
    }
}

int main() {
    int num_states, num_transitions;
    printf("Enter the number of states: ");
    scanf("%d", &num_states);
    printf("Enter the number of transitions: ");
    scanf("%d", &num_transitions);

    struct state nfa[MAX_STATES];
    bool visited[MAX_STATES] = {false};

    // Initialize NFA states
    for (int i = 0; i < num_states; i++) {
        initialize_state(&nfa[i], i);
    }

    // Input transitions
    printf("Enter transitions (state1 state2) :\n");
    for (int i = 0; i < num_transitions; i++) {
        int state1, state2;
        scanf("%d %d", &state1, &state2);
        add_transition(&nfa[state1], state2);
    }

    // Find e-closure for each state
    printf("e-closure of each state:\n");
    for (int i = 0; i < num_states; i++) {
        printf("e-closure(%d): ", i);
        epsilon_closure(nfa, i, visited);
        printf("\n");

        // Reset visited array for next iteration
        for (int j = 0; j < num_states; j++)
            visited[j] = false;
    }

    return 0;
}

