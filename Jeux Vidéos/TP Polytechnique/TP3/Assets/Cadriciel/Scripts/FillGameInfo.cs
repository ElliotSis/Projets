using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class FillGameInfo : MonoBehaviour {

	private GameInfoTransmitter gameInfo;
	private Text text;

	// Use this for initialization
	void Start () {
		gameInfo = GameObject.Find ("GameInfo").GetComponent<GameInfoTransmitter> ();
		text = gameObject.GetComponent<Text> ();

		text.text = "Victoire de " + gameInfo.classement [0] + " !\n"
				+ 	"Temps : " + gameInfo.GetTimer () + "s \n\n"
				+ 	"Position des joueurs : \n";

		for (int i = 0; i < gameInfo.classement.Length; ++i) 
			text.text += (i + 1) + " : " + gameInfo.classement [i] + "\n";
	}
}
