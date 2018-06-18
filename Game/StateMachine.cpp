#include "StateMachine.h"
namespace sg {

	void sg::StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->isAdding = true;
		this->isReplacing = isReplacing;
		this->newState = std::move(newState);
	}

	void sg::StateMachine::RemoveState()
	{
		this->isRemoving = true;
	}

	StateRef & sg::StateMachine::GetActiveState()
	{
		return this->_state.top();
	}

	void sg::StateMachine::ProcessStateChanges()
	{

		if (isRemoving && !this->_state.empty()) {
			this->_state.pop();
			if (!this->_state.empty()) {
				this->_state.top()->Resume();
			}
			isRemoving = false;
		}

		if (this->isAdding) {
			if (!this->_state.empty()) {
				if (this->isReplacing) {
					this->_state.pop();
					this->isReplacing = false;
				}
				else {
					this->_state.top()->Pause();
				}
			}
			this->_state.push(std::move(newState));
			this->_state.top()->Init();
			this->isAdding = false;
		}

	}
}