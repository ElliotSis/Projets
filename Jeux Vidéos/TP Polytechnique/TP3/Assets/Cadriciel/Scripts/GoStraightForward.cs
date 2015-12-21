using UnityEngine;
using System.Collections;

public class GoStraightForward : MonoBehaviour {

	[SerializeField] float speed = 60f;

	// Update is called once per frame
	void Update () {
		transform.position += Time.deltaTime * transform.forward * speed;	
	}
}
