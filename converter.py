# pip install Pillow
from PIL import Image

def convert_to_ppm(input_image_path, output_image_path):
    # Abrir a imagem de entrada
    input_image = Image.open(input_image_path)
    
    # Redimensionar a imagem para 500x500
    resized_image = input_image.resize((500, 500))
    
    # Criar um novo objeto de imagem RGB
    output_image = Image.new("RGB", (500, 500), color='white')
    
    # Colar a imagem redimensionada no canto superior esquerdo do objeto de imagem RGB
    output_image.paste(resized_image, (0, 0))
    
    # Salvar a imagem como PPM
    with open(output_image_path, 'w') as f:
        f.write("P3\n500 500\n255\n")
        pixels = output_image.load()
        for y in range(500):
            for x in range(500):
                r, g, b = pixels[x, y]
                f.write(f"{r} {g} {b} ")
            f.write("\n")

# Exemplo de uso
input_image_path = 'image.jpg'
output_image_path = 'image.ppm'
convert_to_ppm(input_image_path, output_image_path)
