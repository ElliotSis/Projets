using UnityEngine;
using System.Collections;

public class MinimapResizer : MonoBehaviour
{
	private float itsWidth;
	private float itsHeight;
	private Camera itsMinimapCamera = null;
	[SerializeField] private float minimapHeightRatio = 0.3f;

	// Use this for initialization
	void Start ()
	{
		itsMinimapCamera = GetComponent<Camera>();
		itsWidth = itsHeight = minimapHeightRatio;
	}
	
	// Update is called once per frame
	void Update ()
	{
		float posXpixels = Screen.width - itsWidth * Screen.height;
		float posX = posXpixels / Screen.width;
		float posY = 1 - itsHeight;
		itsMinimapCamera.rect = new Rect(posX,posY,itsWidth,itsHeight);
		
	}
}