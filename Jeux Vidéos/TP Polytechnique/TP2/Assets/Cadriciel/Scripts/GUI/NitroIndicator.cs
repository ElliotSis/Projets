using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class NitroIndicator : MonoBehaviour {

	[SerializeField] Image nitro; // The image displaying the player's nitro.
	[SerializeField] Image effect; // The image displaying the speed effect.
	[SerializeField] CarController car; // The car controller.
	[SerializeField] CarNitroManager carNitro; // The car's nitro.

	// Use this for initialization
	void Start () {
		nitro.fillAmount = 0;
		carNitro.consummed += ActivateSpeedEffect;
		car.noNitro += DeActivateSpeedEffect;
		DeActivateSpeedEffect();
	}
	
	// Update is called once per frame
	void Update () {
		nitro.fillAmount = (carNitro.Nitro) / (carNitro.MaxNitro);
	}
	
	void ActivateSpeedEffect() {
		effect.enabled = true;
	}
	
	void DeActivateSpeedEffect() {
		effect.enabled = false;
	}
}
