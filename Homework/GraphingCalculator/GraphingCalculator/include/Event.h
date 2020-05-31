#pragma once

class Event
{
public:
	Event();
	virtual ~Event();

	virtual void Invoke() = 0;

	bool operator==(const Event &rhs) const;
	bool operator!=(const Event &rhs) const;

private:
	int id;
	static int nextID;
};