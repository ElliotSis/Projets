using UnityEngine;
using System.Collections;

public class Destroyable : MonoBehaviour {

	[SerializeField] int nbSecondLive = 6;

	IEnumerator death() {
		yield return new WaitForSeconds(nbSecondLive);
		Destroy(gameObject);
	}

	void OnCollisionEnter(Collision col){
		if (col.gameObject.tag == "Projectile") {
			Destroy(col.gameObject);
			Destroy(gameObject.GetComponent("BoxCollider"));
			foreach (Transform line in transform){
				foreach(Transform cube in line.transform){
					Rigidbody gameObjectsRigidBody = cube.gameObject.AddComponent<Rigidbody>();
					gameObjectsRigidBody.mass = 10.0f;
				}
			}
			StartCoroutine(death());
		}
	}



}
