class Parameters:
    def __init__(self, xi=1.0, beta=0.58, varphi=0.15, numClfrs=1,
                 numFerns=300, numFeats=8, poolSize=10, fernSize=8,
                 trnSamps=100, updSamps=2, recThick=4, textFont=2,
                 imgEqual=False, imageChans=3, saveImgs=False,
                 visuMode=1, imgWidth=640, imgHeight=480, objHeight=18,
                 minCellSize=5, maxCellSize=20, filePath="../files/parameters.txt",
                 colors=None):
        # Add to constructor
        if colors is None:
            colors = [(0, 0, 255), (255, 255, 0), (255, 0, 255), (0, 255, 255), (200, 100, 0),
                      (200, 0, 100), (0, 200, 100), (100, 200, 0), (100, 0, 200), (0, 100, 200),
                      (150, 50, 50), (50, 150, 50), (50, 50, 150), (100, 100, 0), (0, 100, 100),
                      (100, 0, 100), (100, 0, 0), (0, 100, 0), (0, 0, 100), (255, 0, 0)]
        if colors is None:
            colors = [(), (), ()]
        self.__xi = xi  # sensitivity learning rate (xi)
        self.__beta = beta  # classifier threshold (beta)
        self.__varphi = varphi  # image shift (varphi)
        self.__numClfrs = numClfrs  # num. object classifiers (K)
        self.__numFerns = numFerns  # num. random ferns (J)
        self.__numFeats = numFeats  # num. binary features per fern (M)
        self.__poolSize = poolSize  # num. random fern paramaters (R)
        self.__fernSize = fernSize  # spatial fern size (S)
        self.__trnSamps = trnSamps  # num. initial (training) samples (Nt)
        self.__updSamps = updSamps  # num. new (updating) samples (Nu)
        self.__recThick = recThick  # rectangle thickness
        self.__textFont = textFont  # text font
        self.__imgEqual = imgEqual  # image equalization
        self.__imgChans = imageChans  # num. image channels (C)
        self.__saveImgs = saveImgs  # save images in disk
        self.__visuMode = visuMode  # visualization mode
        self.__imgWidth = imgWidth  # image width (Iv)
        self.__imgHeight = imgHeight  # image height (Iu)
        self.__objHeight = objHeight  # standard object height (B_u)
        self.__minCellSize = minCellSize  # min image cell size
        self.__maxCellSize = maxCellSize  # max image cell size
        self.__filePath = filePath
        self.__colors = colors

    def get_learning_rate(self):
        return self.__xi

    def get_num_ferns(self):
        return self.__numFerns

    def get_num_features(self):
        return self.__numFeats

    def get_fern_size(self):
        return self.__fernSize

    def get_num_classifiers(self):
        return self.__numClfrs

    def get_pool_size(self):
        return self.__poolSize

    def get_object_height(self):
        return self.__objHeight

    def get_threshold(self):
        return self.__beta

    def get_image_shift(self):
        return self.__varphi

    def get_rectangle_thiickness(self):
        return self.__recThick

    def get_num_image_channels(self):
        return self.__imgChans

    def get_image_width(self):
        return self.__imgWidth

    def get_image_height(self):
        return self.__imgHeight

    def get_min_cell_size(self):
        return self.__minCellSize

    def get_max_cell_size(self):
        return self.__maxCellSize

    def get_text_font(self):
        return self.__textFont

    def get_save_images(self):
        return self.__saveImgs

    def get_visual_mode(self):
        return self.__visuMode

    def set_visual_mode(self, mode):
        self.__visuMode = mode

    def get_num_train_samples(self):
        return self.__trnSamps

    def get_num_update_samples(self):
        return self.__updSamps

    def image_equalization(self):
        return self.__imgEqual

    def get_color(self, index):
        if index >= len(self.__colors):
            print('Warning: only 10 colors are defined')
            index = 0

        return self.__colors[index]

    def fun_load(self):
        with(open('/home/arttu/PycharmProjects/detector/parameters/parameters.txt')) as file:
            parameters = file.read()

            lines = parameters.split('\n')

            for line in lines:
                key, value = line.split(':')
                if key == 'numClfrs':
                    self.__numClfrs = int(value)
                if key == 'numFerns':
                    self.__numFerns = int(value)
                if key == 'numFeats':
                    self.__numFeats = int(value)
                if key == 'poolSize':
                    self.__poolSize = int(value)
                if key == 'fernSize':
                    self.__fernSize = int(value)
                if key == 'imgChans':
                    self.__imgChans = int(value)
                if key == 'objHeght':
                    self.__objHeight = int(value)
                if key == 'xi':
                    self.__xi = float(value)
                if key == 'beta':
                    self.__beta = float(value)
                if key == 'trnSamps':
                    self.__trnSamps = int(value)
                if key == 'updSamps':
                    self.__updSamps = int(value)
                if key == 'imgWidth':
                    self.__imgWidth = int(value)
                if key == 'imgHeight':
                    self.__imgHeight = int(value)
                if key == 'varphi':
                    self.__varphi = float(value)
                if key == 'minCellSize':
                    self.__minCellSize = int(value)
                if key == 'maxCellSize':
                    self.__maxCellSize = int(value)
                if key == 'imgEqual':
                    self.__imgEqual = int(value)
                if key == 'textFont':
                    self.__textFont = float(value)
                if key == 'recThick':
                    self.__recThick = int(value)
                if key == 'saveImgs':
                    self.__saveImgs = int(value)
                if key == 'visuMode':
                    self.__visuMode = int(value)

    def fun_print(self):
        print("\n*********************************************************")
        print("*               Online Multi-Object Detection           *")
        print("*********************************************************")

        print("\n*********************************************************")
        print("* Program parameters :")
        print("* image size -> " + str(self.__imgHeight) + "x" + str(self.__imgWidth))
        print("* object height -> " + str(self.__objHeight))
        print("* num. image channels -> " + str(self.__imgChans))
        print("* num. object classifiers -> " + str(self.__numClfrs))
        print("* num. random ferns -> " + str(self.__numFerns))
        print("* num. ferns parameters -> " + str(self.__poolSize))
        print("* num. features -> " + str(self.__numFeats))
        print("* fern size -> " + str(self.__fernSize) + "x" + str(self.__fernSize))
        print("* classfier threshold -> " + str(self.__beta))
        print("* num. training samples -> " + str(self.__trnSamps))
        print("* num. updating samples -> " + str(self.__updSamps))
        print("* min. cell size -> " + str(self.__minCellSize))
        print("* max. cell size -> " + str(self.__maxCellSize))
        print("* image shift -> " + str(self.__varphi))
        print("* rec. thickness -> " + str(self.__recThick))
        print("*********************************************************")
