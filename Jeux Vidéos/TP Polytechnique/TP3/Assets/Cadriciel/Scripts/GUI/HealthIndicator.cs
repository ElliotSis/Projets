using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class HealthIndicator : MonoBehaviour {
	
	[SerializeField] Image health; // The image displaying the player's health
	[SerializeField] CarHealthManager carHealth; // The car's health.
	[SerializeField] float displayTime = 1f;
	
	void Awake () {
		gameObject.SetActive(false);
		carHealth.healthLoss += Display;
	}
	
	void UpdateHealth() {
		health.fillAmount = (carHealth.Health) / (carHealth.MaxHealth);
	}
	
	void Display() {
		UpdateHealth ();
		gameObject.SetActive(true);
		StartCoroutine("WaitAndStopDisplaying");
	}
	
	IEnumerator WaitAndStopDisplaying() {
		yield return new WaitForSeconds(displayTime);
		gameObject.SetActive(false);
	}
}