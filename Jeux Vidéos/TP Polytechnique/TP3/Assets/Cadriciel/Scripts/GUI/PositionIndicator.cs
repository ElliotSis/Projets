using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PositionIndicator : MonoBehaviour {
	[SerializeField] CheckpointManager checkPointManager;
	[SerializeField] CarController car;
	
	Text positionText;
	
	// Use this for initialization
	void Start () {
		positionText = GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {
		int lap = checkPointManager.CarPositions[car].lap;
		int checkpoint = checkPointManager.CarPositions[car].checkPoint;
		int position = checkPointManager.CarPositions[car].position;
		
		if (checkPointManager.ValidPositions()) {
			positionText.text = "Lap : " + lap + "\nCheckpoint : " + checkpoint + "\nPosition : " + position;
		}
		else {
			positionText.text = "Lap : \nCheckpoint : \nPosition : ";
		}
	}
}
