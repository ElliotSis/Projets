using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SpeedIndicator : MonoBehaviour {
	[SerializeField] CarController car; // The car to follow
	[SerializeField] GameObject needle; // The needle's rotation
	[SerializeField] Text speedText; // The text displaying the speed
	[SerializeField] float needleMaxRotation = -261.23f; // The maximum rotation of the needle
	float needleSavedAngle = 0.0f; // Current angle
	Vector3 eulerAngleStart;

	void Awake(){
		eulerAngleStart = needle.transform.eulerAngles;
	}

	void Update(){
		if (Vector3.Distance (car.rigidbody.velocity, Vector3.zero) == 0) {
			resetNeedle();
			return;
		}
		float angle = (car.CurrentSpeed > 0f) ? ((car.CurrentSpeed / car.MaxSpeed) * needleMaxRotation - needleSavedAngle) : (0f);
		needle.transform.Rotate(0.0f, 0.0f, angle);
		needleSavedAngle = (car.CurrentSpeed / car.MaxSpeed) * needleMaxRotation;
		// Converting the speed to MPH and displaying it
		speedText.text = ((int)(Mathf.Abs((float)(car.CurrentSpeed * 2.237)))) + " MPH";
	}

	public void resetNeedle(){
		needle.transform.eulerAngles = eulerAngleStart;
		needleSavedAngle = 0;
	}
}
