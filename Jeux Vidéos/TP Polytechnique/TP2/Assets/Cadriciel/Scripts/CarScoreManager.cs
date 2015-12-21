using UnityEngine;
using System.Collections;

public class CarScoreManager : MonoBehaviour {							
	[SerializeField] float airScore = 1.0f;								// The impact of air driving
	[SerializeField] float proximityScore = 1.0f; 						// The impact of proximity driving
	[SerializeField] float minDistance = 2.0f; 							// Distance min for proximity driving
	[SerializeField] float maxDistance = 5.0f; 							// Distance max for proximity driving
	
	private CarController carController;
	
	public float Score {get; private set;}
	
	void Awake() {
		Score = 0.0f;
		carController = GetComponent<CarController>();
	}
	
	void FixedUpdate() {
		UpdateScore();
	}
	
	void UpdateScore() {
		Score += proximityScore * CheckProximity ();
		Score += airScore * CheckAir ();
	}
	
	int CheckProximity () {
		int res = 0;
		foreach (GameObject go in carController.Obstacles) {
			foreach (Transform child in go.GetComponentsInChildren<Transform>()) {
				if (child.parent == go.transform && go != this.gameObject) {
					float distance = Vector3.Distance (transform.position, child.position);
					if (distance > minDistance && distance < maxDistance) {
						res++;
					}
				}
			}
		}
		return res;
	}
	
	int CheckAir() {
		int res = ((carController.AnyOnGround) ? (0) : (1));
		return res;
	}
}
