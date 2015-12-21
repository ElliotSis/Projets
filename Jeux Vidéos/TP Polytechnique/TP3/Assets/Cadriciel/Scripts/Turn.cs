using UnityEngine;
using System.Collections;

public class Turn : MonoBehaviour 
{
	[SerializeField] private RaceManager manager;
	[SerializeField] private string nextDirection;
		
	void OnTriggerEnter(Collider other)
	{
		if (other as WheelCollider == null)
		{
			CarController car = other.transform.GetComponentInParent<CarController>();
			if (car != null && car.GetComponent<CarUserControlMP>() != null) {	
				manager.DisplayDirection(nextDirection);
			}
		}
	}
}
