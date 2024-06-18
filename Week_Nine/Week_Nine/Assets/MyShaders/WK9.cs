using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WK9 : MonoBehaviour
{

    RenderTexture outputTexture;
    Renderer rend;
    public ComputeShader shader;
    int kernelHandle;

    // Start is called before the first frame update
    void Start()
    {
        //Setting up the texture properties and creating it to be
        //painted by the shader
        outputTexture = new RenderTexture(256, 256, 0);
        outputTexture.enableRandomWrite = true;
        outputTexture.Create();

        rend = GetComponent<Renderer>();

        //Initialization of the compute shader that we developed

        //kernelHandle = shader.FindKernel("SolidRed");
        //shader.SetTexture(kernelHandle, "Result", outputTexture);
        // rend.material.SetTexture("_MainTex", outputTexture);

        //shader.Dispatch(kernelHandle, 16, 16, 1);

        int kernelHandle = shader.FindKernel("CheckerBoard");
        shader.SetTexture(kernelHandle, "Result", outputTexture);
        rend.material.SetTexture("_MainTex", outputTexture);
        shader.Dispatch(kernelHandle, 32, 32, 1);

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
