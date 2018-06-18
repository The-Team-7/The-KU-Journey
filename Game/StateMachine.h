#pragma once
#include<memory>
#include<stack>
#include "State.h"

namespace sg {
	typedef std::unique_ptr<State> StateRef;

	////// STATE MACHINE CLASS STORES AND MANAGES THE STATES USED IN THE GAME /////
	////// IT HELPS IN TRANSITION BEWTEEN DIFFERENT STATES  /////

	class StateMachine
	{
	public:
		void AddState(StateRef newState, bool isReplaing);
		void RemoveState();
		StateRef& GetActiveState();
		void ProcessStateChanges();

	private:
		std::stack<StateRef> _state;
		StateRef newState;

		bool isReplacing;
		bool isAdding;
		bool isRemoving;
	};
}




