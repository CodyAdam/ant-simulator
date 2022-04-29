#ifndef _Timer_H
#define _Timer_H

/// <summary>
/// A timer class.
/// </summary>
class Timer
{
protected:
	static float m_currentTime;
	static float m_deltaTime;
	static int m_fps;
	static int m_tps;

public:
	/// <summary>
	/// Returns the absolute time since the beginning of the simulation.
	/// </summary>
	/// <returns></returns>
	static float time()
	{
		return m_currentTime;
	}

	/// <summary>
	/// Returns the time elapsed since the last time step.
	/// </summary>
	/// <returns></returns>
	static float dt()
	{
		return m_deltaTime;
	}

	/// <summary>
	/// Updates the time with specified time step duration.
	/// </summary>
	/// <param name="dt">The time step duration.</param>
	static void update(float dt)
	{
		m_currentTime += dt;
		m_deltaTime = dt;
	}

	/// <returns>Returns the number of frames per second.</returns>
	static int fps()
	{
		return m_fps;
	}

	/// <returns>Returns the number of time steps per second.</returns>
	static int tps()
	{
		return m_tps;
	}

	/// <summary>
	/// Updates the TPS.
	/// </summary>
	static void setTps(int tps)
	{
		m_tps = tps;
	}

	/// <summary>
	/// Updates the FPS.
	/// </summary>
	static void setFps(int fps)
	{
		m_fps = fps;
	}
};

#endif