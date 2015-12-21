using UnityEngine;
using System.Collections;

public class Accelerator : MonoBehaviour {

	[SerializeField] private float boostPower = 20.0f;
	
	void OnCollisionEnter(Collision collision) {
		if (collision.gameObject.name == "Joueur 1") {
			collision.rigidbody.AddRelativeForce (new Vector3(0,0,boostPower), ForceMode.Impulse);
		}
	}
}