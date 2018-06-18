#pragma once
namespace sg {

	//////// THIS IS THE INTERFACE CLASS WHICH DEFINES HOW A GAME STATE SHOULD WORK AND FUNCTION //////

	class State
	{
	public:
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(float dt) = 0;

		virtual void Pause() { };
		virtual void Resume() { };
			
	};

}