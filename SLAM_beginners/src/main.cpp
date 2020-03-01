#include "SlamLauncher.h"

int main(int argc, char* argv[]) {
	bool scanCheck = false;   // �X�L�����\���݂̂�
	bool odometryOnly = false; // �I�h���g���ɂ��n�}�\�z��
	char* filename; // �f�[�^�t�@�C����
	int startN = 0; // �J�n�X�L�����ԍ�

	if (argc < 2) {
		printf("Error: too few arguments.\n");
		return(1);
	}

	// �R�}���h�����̏���
	int idx = 1;
	// �R�}���h�I�v�V�����̉���('-'�̂�������)
	if (argv[1][0] == '-') {
		for (int i = 1; ; i++) {
			char opinion = argv[1][i];
			if (opinion == NULL) break;
			else if (opinion == 's') scanCheck = true; // �X�L�����\���̂�
			else if (opinion == 'o') odometryOnly = true; // �I�h���g���ɂ��n�}�\�z
		}
		if (argc == 2) {
			printf("Error: no file name.\n");
			return(1);
		}
		idx++;
	}
	if (argc >= idx + 1) filename = argv[idx]; // '-'����ꍇidx=2, �Ȃ��ꍇidx=1
	if (argc == idx + 2) startN = atoi(argv[idx + 1]); // argc��idx���2�傫�����startN������
	else if (argc >= idx + 2) {
		printf("Error: invalid arguments.\n");
		return(1);
	}

	// �t�@�C�����J��
	SlamLauncher sl;
	bool flag = sl.setFilename(filename);
	if (!flag) return(1);

	sl.setStartN(startN); // �J�n�X�L�����ԍ��̐ݒ�

	// �����{��
	if (scanCheck) sl.showScans();
	else { // �X�L�����\���ȊO��SlamLauncher���ŏꍇ����
		sl.setOdometryOnly(odometryOnly);
		sl.customizeFramework();
		sl.run();
	}

	return(0);
}