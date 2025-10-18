#ifndef FSM_H
#define FSM_H

#include <stddef.h> // For NULL

// --- Public Types ---

/**
 * @brief A type to identify states. Using 'int' is flexible.
 */
typedef int fsm_state_id_t;

/**
 * @brief Function pointer for a state.
 * This is the core of the FSM. Each state is just a function.
 *
 * @param input_data  A const void pointer to any user-defined input data struct.
 * @param output_data A void pointer to any user-defined output data struct.
 * @return            The fsm_state_id_t of the *next* state to transition to.
 */
typedef fsm_state_id_t (*fsm_state_func_t)(const void *input_data, void *output_data);

/**
 * @brief The FSM control structure (the "machine" itself).
 */
typedef struct {
    fsm_state_func_t *states;       // Array of all state functions
    fsm_state_id_t   current_state; // The FSM's current state ID
    fsm_state_id_t   num_states;    // Total number of states
} fsm_t;


// --- Public API Functions ---

/**
 * @brief Initializes a state machine instance.
 * (Functions definitions are the same as before)
 */
void fsm_init(fsm_t *fsm, fsm_state_func_t *states, fsm_state_id_t num_states, fsm_state_id_t initial_state);

/**
 * @brief Runs one "tick" or "step" of the state machine.
 */
void fsm_run(fsm_t *fsm, const void *input_data, void *output_data);

/**
 * @brief Gets the current state ID of the FSM.
 */
fsm_state_id_t fsm_get_current_state(const fsm_t *fsm);

/**
 * @brief Forcibly sets the FSM to a new state.
 */
void fsm_set_current_state(fsm_t *fsm, fsm_state_id_t new_state);


// --- Ergonomic Macros ---

/**
 * @brief Begins the definition of a state function.
 *
 * This is the standard macro. It creates 'in' and 'out'
 * variables and gives the state a local ID for FSM_STAY().
 *
 * @param state_id   The ID of this state (e.g., STATE_RED).
 * @param func_name  The name you want to give the function (e.g., state_red_func).
 * @param in_type    The C type of your input struct (e.g., input_t).
 * @param out_type   The C type of your output struct (e.g., output_t).
 */
#define FSM_DEFINE_STATE(state_id, func_name, in_type, out_type) \
    fsm_state_id_t func_name(const void *input_data, void *output_data) { \
        const fsm_state_id_t FSM_CURRENT_STATE_ID = (state_id); \
        const in_type *in = (const in_type *)input_data; \
        out_type *out = (out_type *)output_data; \
        (void)FSM_CURRENT_STATE_ID; \
        (void)in; \
        (void)out;

/**
 * @brief Ends a state definition.
 */
#define FSM_END_STATE }

/**
 * @brief Returns the ID of the next state to transition to.
 */
#define FSM_TRANSITION(next_state_id) return (next_state_id)

/**
 * @brief Explicitly stay in the current state.
 */
#define FSM_STAY() return (FSM_CURRENT_STATE_ID)

#endif // FSM_H