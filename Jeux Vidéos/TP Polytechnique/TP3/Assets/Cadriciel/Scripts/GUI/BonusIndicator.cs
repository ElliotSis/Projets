using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class BonusIndicator : MonoBehaviour {
	[SerializeField] Text nothing;
	[SerializeField] Image greenBall;
	[SerializeField] Image redBall;
	[SerializeField] Image blueBall;
	[SerializeField] GameObject car;
	
	// Use this for initialization
	void Awake () {
		SetNoObject();
	}

	void Update(){
		string color = car.GetComponent<Shooter>().GetColor();
		if (color == "Null")
			SetNoObject ();
		if (color == "Red")
			SetRedBall ();
		if (color == "Blue")
			SetBlueBall ();
		if (color == "Green")
			SetGreenBall ();
	}
	
	void SetRedBall() {
		SetNoObject ();
		redBall.enabled = true;
	}
	
	void SetGreenBall() {
		SetNoObject ();
		greenBall.enabled = true;
	}
	
	void SetBlueBall() {
		SetNoObject ();
		blueBall.enabled = true;
	}
	
	void SetNoObject() {
		nothing.enabled = true;
		greenBall.enabled = false;
		redBall.enabled = false;
		blueBall.enabled = false;
	}
}
