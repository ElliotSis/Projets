using UnityEngine;
using System.Collections;

public class WaterRescue : MonoBehaviour {

	[SerializeField] float nbSecondRescue = 2.0f;
	[SerializeField] PathIndicator pathIndicator;

	IEnumerator rescued(Transform collider) {
		if(collider.gameObject.name == "Joueur 1")
			pathIndicator.Display ("Stop");
		yield return new WaitForSeconds(nbSecondRescue);
		collider.GetComponent<Rescue> ().rescuePosition ();
		if(collider.gameObject.name == "Joueur 1")
			pathIndicator.StopDisplaying ("Stop");
	}

	void OnTriggerEnter(Collider col){
		if(col.transform.parent != null){
			Transform collider = col.transform.parent.gameObject.transform.parent;
			if (collider != null && collider.tag == "Player") {
				StartCoroutine(rescued(collider));
			}
		}
	}


}
