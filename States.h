#pragma once

class State // This is the abstract base class for all states
{
public:
	//State() = default;
	//virtual ~State() = default; // Modern alternative to {}

	virtual void Enter() = 0; // 0 means pure virtual - must be defined in subclass
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Resume() { };
};

