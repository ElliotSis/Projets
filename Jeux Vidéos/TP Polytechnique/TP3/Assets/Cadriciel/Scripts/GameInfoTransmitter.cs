using UnityEngine;
using System.Collections;

public class GameInfoTransmitter : MonoBehaviour {

	public string[] classement;
	private float temps = 0f;

	private bool timerStarted = false;

	// Use this for initialization
	void Start () {
		DontDestroyOnLoad (gameObject);
		classement = new string[7];
	}

	void Update() {
		temps += Time.deltaTime;
	}

	public void StartTimer() {
		timerStarted = true;
	}

	public void StopTimer() {
		timerStarted = false;
	}

	public float GetTimer() {
		return temps;
	}
}
