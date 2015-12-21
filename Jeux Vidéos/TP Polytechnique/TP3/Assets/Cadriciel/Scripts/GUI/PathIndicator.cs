using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PathIndicator : MonoBehaviour {

	[SerializeField] private Image left;
	[SerializeField] private Image right;
	[SerializeField] private Image stop;
	[SerializeField] private float displayTime = 1f;
	
	void Awake() {
		StopDisplaying();
	}

	public void Display(string direction) {
		left.enabled = (direction == "Left" || direction == "All");
		right.enabled = (direction == "Right" || direction == "All");
		stop.enabled = (direction == "Stop" || direction == "All");
		StartCoroutine("WaitAndStopDisplaying");
	}
	
	IEnumerator WaitAndStopDisplaying() {
		yield return new WaitForSeconds(displayTime);
		StopDisplaying();
	}
	
	public void StopDisplaying(string direction = "All") {
		left.enabled = left.enabled && !(direction == "Left" || direction == "All");
		right.enabled = right.enabled && !(direction == "Right" || direction == "All");
		stop.enabled = stop.enabled && !(direction == "Stop" || direction == "All");
	}
}
