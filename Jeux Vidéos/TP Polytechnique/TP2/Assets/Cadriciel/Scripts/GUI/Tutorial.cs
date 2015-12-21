using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Tutorial : MonoBehaviour {
	[SerializeField] CarController car;
	[SerializeField] string basicTutorial;
	[SerializeField] string airTutorial;
	
	Text tutorial;
	
	// Use this for initialization
	void Start () {
		tutorial = GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {
		if (car.AnyOnGround) {
			tutorial.text = basicTutorial;
		}
		else {
			tutorial.text = airTutorial;
		}
	}
}
