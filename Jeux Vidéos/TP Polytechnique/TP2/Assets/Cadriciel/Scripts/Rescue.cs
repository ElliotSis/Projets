using UnityEngine;
using System.Collections;

public class Rescue : MonoBehaviour {
	[SerializeField] Transform target;
	[SerializeField] PathIndicator pathIndicator;
	[SerializeField] float distMax = 80.0f;
	[SerializeField] float distStop = 70.0f;
	float noShowTime = 2f;

	void Update(){
		if (Vector3.Distance (target.position, transform.position) > distStop && noShowTime < Time.timeSinceLevelLoad) {
			pathIndicator.Display ("Stop");
		} else {
			pathIndicator.StopDisplaying ("Stop");
		}
		if (Vector3.Distance (target.position, transform.position) > distMax) {
			GetComponent<Rigidbody> ().velocity = new Vector3 (0, 0, 0);
			transform.position = target.position;
			transform.forward = target.forward;
		}
	}
}