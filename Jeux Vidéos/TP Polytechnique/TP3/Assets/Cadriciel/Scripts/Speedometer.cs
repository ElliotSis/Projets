using UnityEngine;
using UnityEngine.UI;
using System.Collections;

[RequireComponent(typeof(CarController))]

public class Speedometer : MonoBehaviour {
	[SerializeField] GameObject player; // The player to follow
	float max_rot = -261.23f;
	CarController car;
	float savedAngle = 0.0f;

	void Awake(){
		car = player.GetComponent<CarController>();
	}

	void Update(){
		float angle = (car.CurrentSpeed / car.MaxSpeed) * max_rot - savedAngle;
		transform.Rotate(0,0,angle);
		savedAngle = (car.CurrentSpeed / car.MaxSpeed) * max_rot;
	}
}
