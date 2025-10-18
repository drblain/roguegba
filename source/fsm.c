#include "fsm.h"
#include <assert.h> // For safety checks

void fsm_init(fsm_t *fsm, fsm_state_func_t *states, fsm_state_id_t num_states, fsm_state_id_t initial_state) {
    // Use assertions to catch common setup errors
    assert(fsm != NULL);
    assert(states != NULL);
    assert(num_states > 0);
    assert(initial_state < num_states); // Ensure initial state is valid

    fsm->states = states;
    fsm->num_states = num_states;
    fsm->current_state = initial_state;
}

void fsm_run(fsm_t *fsm, const void *input_data, void *output_data) {
    assert(fsm != NULL);
    assert(fsm->states != NULL);

    // Ensure the current state is valid before trying to access it
    assert(fsm->current_state < fsm->num_states);

    // 1. Get the function pointer for the current state
    fsm_state_func_t current_state_func = fsm->states[fsm->current_state];

    // 2. Execute the state function
    // It runs its logic and returns the ID of the next state.
    fsm_state_id_t next_state = current_state_func(input_data, output_data);

    // 3. Update to the next state
    // Ensure the next state is also valid before setting it
    assert(next_state < fsm->num_states);
    fsm->current_state = next_state;
}

fsm_state_id_t fsm_get_current_state(const fsm_t *fsm) {
    assert(fsm != NULL);
    return fsm->current_state;
}

void fsm_set_current_state(fsm_t *fsm, fsm_state_id_t new_state) {
    assert(fsm != NULL);
    assert(new_state < fsm->num_states); // Ensure new state is valid
    fsm->current_state = new_state;
}