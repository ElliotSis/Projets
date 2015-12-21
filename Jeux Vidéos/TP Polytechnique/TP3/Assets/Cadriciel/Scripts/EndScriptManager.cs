using UnityEngine;
using System.Collections;

public class EndScriptManager : MonoBehaviour {

	// Use this for initialization
	void Awake () {
		Input.simulateMouseWithTouches = true;
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0)) {
			DestroyObject(GameObject.Find("GameInfo"));
			Application.LoadLevel("newCourse");
		} 
		else if (Input.GetKeyDown(KeyCode.Escape)) {
			Application.Quit();
		}
	}
}
