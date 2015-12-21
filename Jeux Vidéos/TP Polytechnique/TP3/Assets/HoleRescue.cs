using UnityEngine;
using System.Collections;

public class HoleRescue : MonoBehaviour {

	[SerializeField] float nbSecondRescue = 5.0f;
	[SerializeField] Transform waypoint;
	[SerializeField] Transform secondWaypoint;
	[SerializeField] PathIndicator pathIndicator;
	
	IEnumerator rescued(Transform collider) {
		pathIndicator.Display ("Stop");
		yield return new WaitForSeconds(nbSecondRescue);
		collider.GetComponent<Rescue> ().rescuePosition (waypoint);
		collider.forward = secondWaypoint.position - waypoint.position;
		pathIndicator.StopDisplaying ("Stop");
	}
	
	void OnTriggerEnter(Collider col){
		if (col.transform.parent != null) {
			Transform collider = col.transform.parent.gameObject.transform.parent;
			if (collider != null && collider.tag == "Player") {
				StartCoroutine (rescued (collider));
			}
		}
	}
}
