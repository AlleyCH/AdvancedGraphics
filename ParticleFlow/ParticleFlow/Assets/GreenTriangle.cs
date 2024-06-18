using UnityEngine;

[RequireComponent(typeof(MeshFilter))]
[RequireComponent(typeof(MeshRenderer))]
public class GreenTriangle : MonoBehaviour
{
    void Start()
    {
        Mesh mesh = new Mesh();
        mesh.vertices = GenerateVertices();
        mesh.triangles = GenerateTriangles();
        mesh.RecalculateNormals();
        GetComponent<MeshFilter>().mesh = mesh;
    }

    Vector3[] GenerateVertices()
    {
        return new Vector3[]
        {
            new Vector3(-0.5f, -0.5f, 0f), // Bottom-left
            new Vector3(0.5f, -0.5f, 0f),  // Bottom-right
            new Vector3(0f, 0.5f, 0f)      // Top-middle
        };
    }

    int[] GenerateTriangles()
    {
        return new int[] { 0, 1, 2 };
    }
}
