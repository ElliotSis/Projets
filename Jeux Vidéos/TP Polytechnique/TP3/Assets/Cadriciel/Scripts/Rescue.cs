using UnityEngine;
using System.Collections;

public class Rescue : MonoBehaviour {
	[SerializeField] Transform target;
	[SerializeField] float threshold = 5.0f;
	[SerializeField] float timeIdleBeforeRescue = 4.0f;
	private Vector3 lastPositionIdle;
	private float timeIdle = 0.0f;
	bool start;
	

	WaypointCircuit waypoint;

	public void rescuePosition(Transform rescuePoint = null){
		if (rescuePoint == null){
			GetComponent<Rigidbody> ().velocity = new Vector3 (0, 0, 0);
			rescuePoint = waypoint.getClosestPoint (transform);
		}
		transform.position = rescuePoint.position;
		transform.forward = rescuePoint.forward;
		timeIdle = 0.0f;
		lastPositionIdle = transform.position;
	}

	void Start(){
		waypoint = target.GetComponent<WaypointCircuit> ();
		lastPositionIdle = transform.position;
	}

	void Update(){
		if(!start){
			if(GetComponent<CarAIControl>() != null)
				start = GetComponent<CarAIControl>().enabled;
			if(GetComponent<CarUserControlMP>() != null)
				start = GetComponent<CarUserControlMP>().enabled;
	    } else {
			if (Vector3.Distance (transform.position, lastPositionIdle) > threshold) {
				lastPositionIdle = transform.position;
				timeIdle = 0.0f;
			} else {
				if(timeIdle > timeIdleBeforeRescue){
					rescuePosition();
				} else {
					timeIdle+=Time.deltaTime;
				}
			}
		}
	}

	
}