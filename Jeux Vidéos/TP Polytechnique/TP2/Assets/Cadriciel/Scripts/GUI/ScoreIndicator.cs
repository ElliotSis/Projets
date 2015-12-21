using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ScoreIndicator : MonoBehaviour {
	[SerializeField] CarScoreManager carScore; // The car's score.
	[SerializeField] int increasingScoreFontSize = 22;
	
	private int previousScore = 0; // The previous score of the player
	private int fontSize;
	private Text displayText; // The text element to display
	
	void Awake() {
		displayText = GetComponent<Text>();	
		fontSize = displayText.fontSize;
	}
	
	void Update(){
		displayText.text = "Score : " + (int)carScore.Score;
		if (previousScore < (int)carScore.Score) {
			displayText.fontSize = increasingScoreFontSize;
		}
		else {
			displayText.fontSize = fontSize;
		}
		previousScore = (int)carScore.Score;
	}
	

}