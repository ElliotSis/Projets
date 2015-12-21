using UnityEngine;
using System.Collections;

[RequireComponent(typeof(GUIText))]
public class Score : MonoBehaviour {
	private int score; // The score of the player
	[SerializeField] GameObject player; // The player to follow
	[SerializeField] GameObject cars; // All the cars in the race
	[SerializeField] int proximityScore = 1; // The increment for proximity driving
	//[SerializeField] int airScore = 1; // The increment for air driving
	[SerializeField] float distance_min = 2.0f; // Distance min for proximity driving
	[SerializeField] float distance_max = 5.0f; // Distance max for proximity driving

	void Update(){
		//The player has to be active
		if (player.activeInHierarchy) {
			//All the things that can improve your score
			score += proximityScore * CheckProximity ();
		}
		guiText.text = "Score = " + score;
	}

	//Return the number of cars near the player
	int CheckProximity () {
		int res = 0;
		foreach (Transform child in cars.transform) {
			float distance = Vector3.Distance (player.transform.position, child.position);
			if (distance > distance_min && distance < distance_max) {
				res++;
			}
		}
		return res;
	}

}