using UnityEngine;
using System.Collections;

public class FollowNearestPlayer : MonoBehaviour {
	
	Transform target;
	GameObject cars;

	[SerializeField] string carsName = "Cars";

	void Awake() {
		cars = GameObject.Find (carsName);




	}

	// Update is called once per frame
	void Update () {
		transform.LookAt (target.position);
	}
}
