#ifndef MAJKT_ENGINE_TIMESTEP_H_
#define MAJKT_ENGINE_TIMESTEP_H_

namespace majkt 
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: time_(time)
		{}

		operator float() const { return time_; }

		float GetSeconds() const { return time_; }
		float GetMilliseconds() const { return time_ * 1000.0f; }
	private:
		float time_;
	};
} // namespace majkt

#endif  // MAJKT_ENGINE_TIMESTEP_H_
